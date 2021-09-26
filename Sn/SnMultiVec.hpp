#ifndef _SnMultiVec
#define _SnMultiVec

#include "SnPart.hpp"
#include "SnType.hpp"
#include "SnMultiPart.hpp"
#include "indexed_map.hpp"


namespace Snob2{

  class SnMultiVec{
  public:

    indexed_mapB<IntegerPartition,SnMultiPart> parts;

    ~SnMultiVec(){
    }


  public:


    SnMultiVec(){}

    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnMultiVec(const int _N, const SnType& _type, const FILLTYPE& fill, const int _dev=0){
      for(auto& p:_type.map)
	parts.insert(p.first,new SnMultiPart(_N,p.first,p.second,fill,_dev));
    }
    
    SnMultiVec(SnMultiPart* part){
      parts.insert(part->get_lambda(),part);
    }


  public: // ---- Named constructors -------------------------------------------------------------------------


    static SnMultiVec zero(const int _N, const SnType& _type, const int _dev=0){
      return SnMultiVec(_N,_type,cnine::fill::zero,_dev);
    }

    static SnMultiVec identity(const int _N, const SnType& _type, const int _dev=0){
      return SnMultiVec(_N,_type,cnine::fill::identity,_dev);
    }

    static SnMultiVec gaussian(const int _N, const SnType& _type, const int _dev=0){
      return SnMultiVec(_N,_type,cnine::fill::gaussian,_dev);
    }


  public: // ---- Copying ------------------------------------------------------------------------------------


    SnMultiVec(const SnMultiVec& x){
      parts=x.parts;
    }

    SnMultiVec(SnMultiVec&& x){
      parts=std::move(x.parts);
    }

    SnMultiVec& operator=(const SnMultiVec& x){
      parts=std::move(x.parts);
      return *this;
    }

    SnMultiVec& operator=(SnMultiVec&& x){
      parts=std::move(x.parts);
      return *this;
    }


  public: // ---- Conversions --------------------------------------------------------------------------------


    SnMultiVec(const SnFunction& f){
      parts.push_back(new SnMultiPart(f));
    }

    SnMultiVec(const SnOverSmFunction& f){
      parts.push_back(new SnMultiPart(f));
    }

    SnFunction as_function(const int _n) const{
      assert(parts.size()==1);
      return parts[0]->as_function(_n);
    }

    SnOverSmFunction as_function(const int _n, const int _m) const{
      assert(parts.size()==1);
      return parts[0]->as_function(_n,_m);
    }



    SnMultiVec(const SnVec& x){
      for(auto p:x.parts)
	parts.push_back(new SnMultiPart(*p));
    }

    SnVec as_vec(){
      SnVec R;
      for(auto p:parts)
	R.parts.push_back(new SnPart(std::move(*p)));
      return R;
    }





  public: // ---- Access -------------------------------------------------------------------------------------


    int getn() const{
      assert(parts.size()>0);
      return parts[0]->getn();
    }
    
    int getN() const{
      assert(parts.size()>0);
      return parts[0]->getN();
    }

    /*
    int index(const IntegerPartition& lambda) const{
      for(int i=0; i<parts.size(); i++)
	if(parts[i]->irrep->lambda==lambda) return i;
      return -1;
    }
    */


  public: // ---- Operations ---------------------------------------------------------------------------------


    /*
    SnMultiVec apply(const SnElement& sigma) const{
      SnMultiVec R;
      for(auto p: parts){
	SnMultiPart* A=new SnMultiPart(*p);
	A->apply_inplace(sigma);
	R.parts.insert(p->get_lambda(),A);
      }
      return R;
    }

    SnMultiVec& apply_inplace(const SnElement& sigma){
      for(auto p:parts)
	p->apply_inplace(sigma);
      return *this;
    }

    SnMultiVec& apply_inplace(const ContiguousCycle& cyc){
      for(auto p:parts)
	p->apply_inplace(cyc);
      return *this;
    }
    */

    SnMultiVec& apply_inplace_inv(const ContiguousCycle& cyc, const int o, const int s=1){
      for(auto p:parts)
	p->apply_inplace_inv(cyc,o,s);
      return *this;
    }
    

  public: // ---- Cumulative operations ----------------------------------------------------------------------


    /*
    void add(const SnMultiVec& y){
      assert(parts.size()==y.parts.size());
      for(int i=0; i<parts.size(); i++)
	parts[i]->add(*y.parts[i]);
    }
    */


  public: // ---- Operations ---------------------------------------------------------------------------------


    SnMultiVec reduce() const{
      SnMultiVec R;
      for(auto p:parts)
	R.parts.push_back(new SnMultiPart(p->reduce()));
      return R;
    }

    SnMultiVec broadcast(const int _N) const{
      SnMultiVec R;
      for(auto p:parts)
	R.parts.push_back(new SnMultiPart(p->broadcast(_N)));
      return R;
    }

    /*
    SnMultiVec static down(const SnMultiPart& v){
      SnMultiVec R;
      int offs=0;
      v.get_lambda().foreach_sub([&](const IntegerPartition& lambda){
	  auto P=new SnMultiPart(v.N,lambda,1,cnine::fill::zero);
	  v.add_block_to(offs,0,*P);
	  R.parts.insert(lambda,P);
	  offs+=P->getd();
	});
      //cout<<R<<endl;
      return R;
    }

    SnMultiVec static up(const SnType& tau, const SnMultiVec& v){
      SnMultiVec R(v.getN(),tau,cnine::fill_zero());
      vector<int> offs(v.parts.size(),0);
      //cout<<tau<<endl;
      for(auto& p:tau.map){
	SnMultiPart& dest=*R.parts[R.index(p.first)];
	int m=dest.dims(1);
	int voffs=0;
	p.first.foreach_sub([&](const IntegerPartition& mu){
	    int ix=v.index(mu);
	    assert(ix>=0);
	    dest.add_to_block_block(voffs,0,*v.parts[ix],0,offs[ix],v.parts[ix]->dims(0),m);
	    voffs+=v.parts[ix]->dims(0);
	    offs[ix]+=m;
	  });
      }
      return R;
    }

    SnMultiVec static cat(const vector<SnMultiVec>& v){
      SnType tau;
      for(int i=0; i<v.size(); i++)
	for(auto p: v[i].parts)
	  tau.add(p->get_lambda(),p->getm());
      SnMultiVec R(v[0].getN(),tau,cnine::fill::zero);
      vector<int> offs(R.parts.size(),0);
      for(int i=0; i<v.size(); i++)
	for(auto p: v[i].parts){
	  int ix=R.index(p->irrep->lambda);
	  R.parts[ix]->add_to_block(0,offs[ix],*p);
	  offs[ix]+=p->dims(1);
	}
      return R;
    }
    */


  public:

    string str(string indent="") const{
      ostringstream oss;
      for(auto p:parts){
	oss<<*p<<endl;
      }
      return oss.str();
    }

    friend ostream& operator<<(ostream& stream, const SnMultiVec& x){
      stream<<x.str(); return stream;
    }

  };


  //inline SnVec operator*(const SnElement& sigma, const SnMultiVec& v){
  //return v.apply(sigma);
  //}

}

#endif
    /*
    operator SnVec() const &{
      cout<<*this<<endl;
      SnVec R;
      for(auto p:parts)
	R.parts.push_back(new SnPart(*p));
      cout<<R<<endl;
      return R;
    }
    */

    /*
    operator SnVec()&&{
      SnVec R;
      for(auto p:parts)
	R.parts.push_back(new SnPart(std::move(*p)));
      parts.clear();
      return R;
    }
    */
