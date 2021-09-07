#ifndef _SnVec
#define _SnVec

#include "SnPart.hpp"
#include "SnType.hpp"
//#include "SnMultiVec.hpp"
//#include "SnModule.hpp"
//#include "SnRepresentation.hpp"

namespace Snob2{

  class SnVec{
  public:

    //SnRepresentationObj* repr;
    vector<SnPart*> parts;

    ~SnVec(){
      for(auto p:parts) delete p;
    }

  public:

    SnVec(){}

    /*
    template<typename FILLTYPE>
    SnVec(const SnRepresentationObj* _repr, const FILLTYPE& fill, const int _dev=0): repr(_repr){
      for(auto& p:M.irreps)
	parts.push_back(new SnPart(p.first,p.second,fill,_dev));
    }
    */

    /*
    template<typename FILLTYPE>
    SnVec(const SnType& _type, const FILLTYPE& fill, const int _dev=0):
      SnVec(_snrepbank->get_rep(_type),fill,dev){}
    */

    /*
    template<typename FILLTYPE>
    SnVec(const SnRepresentation& M, const FILLTYPE& fill, const int _dev=0):
      SnVec(M.obj,fill,dev){}
    */

    SnVec(SnPart* part){
      parts.push_back(part);
    }

    //SnVec(const SnVec& x)=delete;
    //SnVec& operator=(const SnVec& x)=delete;


  public:

    /*
    static SnVec zero(const SnType& _type, const int _dev=0){
      return SnVec(_type,cnine::fill::zero,_dev);
    }

    static SnVec identity(const SnType& _type, const int _dev=0){
      return SnVec(_type,cnine::fill::identity,_dev);
    }

    static SnVec gaussian(const SnType& _type, const int _dev=0){
      return SnVec(_type,cnine::fill::gaussian,_dev);
    }
    */

  public: // ---- Copying ------------------------------------------------------------------------------------


    SnVec(const SnVec& x){
      for(auto p: x.parts)
	parts.push_back(new SnPart(*p));
    }

    SnVec(SnVec&& x){
      parts=x.parts;
      x.parts.clear();
    }

    SnVec& operator=(const SnVec& x){
      for(auto p: parts) delete p;
      parts.clear();
      for(auto p: x.parts)
	parts.push_back(new SnPart(*p));
      return *this;
    }

    SnVec& operator=(SnVec&& x){
      for(auto p: parts) delete p;
      parts=x.parts;
      x.parts.clear();
      return *this;
    }



  public: // ---- Access -------------------------------------------------------------------------------------

    
    

  public:

    SnVec apply(const SnElement& sigma) const{
      SnVec R;
      for(auto p: parts){
	SnPart* A=new SnPart(*p);
	A->apply_inplace(sigma);
	R.parts.push_back(A);
      }
      return R;
    }

    SnVec& apply_inplace(const SnElement& sigma){
      for(auto p:parts)
	p->apply_inplace(sigma);
      return *this;
    }

    SnVec& apply_inplace(const ContiguousCycle& cyc){
      for(auto p:parts)
	p->apply_inplace(cyc);
      return *this;
    }


  public: // ---- Cumulative operations ----------------------------------------------------------------------


    void add(const SnVec& y){
      assert(parts.size()==y.parts.size());
      for(int i=0; i<parts.size(); i++)
	parts[i]->add(*y.parts[i]);
    }


  public: // ---- Fourier transforms ------------------


    /*
    static SnVec Fourier(const FunctionOnGroup<Sn,rtensor>& f){
      const int n=f.G.getn();
      vector<SnMultiVec*> levels(n);
      cout<<0<<endl;
      levels[0]=new SnMultiVec(f);
      for(int l=1; l<n; l++){
	cout<<l<<endl;
	levels[l]=new SnMultiVec(levels[l-1]->uptransform());
	delete levels[l-1];
      }
      return SnVec(std::move(*levels[n-1]));
    }

    SnVec(const SnMultiVec& x){
      assert(x.N==1);
      for(auto p:x.parts)
	parts.push_back(new SnPart(*p.second));
    }

    SnVec(SnMultiVec&& x){
      assert(x.N==1);
      for(auto p:x.parts)
	parts.push_back(new SnPart(p.second->irrep,std::move(*p.second)));
      //parts.push_back(p->convert_to_part_destrictively());
    }
    */

    /*
    SnVec induce() const{
      SnRepresentationObj* induced_rep=repr->get_induced();
      SnVec v(induced_rep,cnine::fill::zero);

      int iso_ix=0;
      for(auto& p:induced_rep.isotypics){
	const SnIsotypicObj& iso=p.second;
	SnPart& part=*v.parts[iso_ix];

	int ioffs=0;
	int joffs=0;
	for(auto subp:iso.subs){
	  const SnPart& sub
	  const int I=
	  for(int i=0; i<
	}

	iso_ix++;
      }
      return v;
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

    friend ostream& operator<<(ostream& stream, const SnVec& x){
      stream<<x.str(); return stream;
    }

  };


  inline SnVec operator*(const SnElement& sigma, const SnVec& v){
    return v.apply(sigma);
  }

}

#endif
    /*
    template<typename FILLTYPE>
    SnVec(const SnModule& M, const FILLTYPE& fill, const int _dev=0){
      for(auto& p:M.map)
	parts.push_back(new SnPart(p.first,p.second,fill,_dev));
      //parts.push_back(new SnPart(p.first,p.second,fill,_dev));
    }
    */
