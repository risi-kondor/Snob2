#ifndef _SnMultiVec
#define _SnMultiVec

#include "SnMultiPart.hpp"
#include "SnType.hpp"

namespace Snob2{

  typedef cnine::RtensorObj rtensor;


  class SnMultiVec{
  public:

    int N;

    //vector<SnMultiPart*> parts;
    //mutable map<IntegerPartition,SnMultiPart*> parts;
    indexed_mapB<IntegerPartition,SnMultiPart> parts;


    ~SnMultiVec(){
      for(auto p:parts) delete p.second;
    }


  public: // ---- Constructors ------------------------------------------------------------------------------


    SnMultiVec(const int _N): N(_N){}

    template<typename FILLTYPE>
    SnMultiVec(int _N, const SnType& _type, const FILLTYPE& fill, const int _dev=0): N(_N){
      for(auto& p:_type.map)
	parts[p.first]=new SnMultiPart(_N,p.first,p.second,fill,_dev);
      //parts.push_back(new SnMultiPart(_N,p.first,p.second,fill,_dev));
    }

    /*
    template<typename FILLTYPE>
    SnMultiVec(int _N, const SnRepresentation& _mu, const FILLTYPE& fill, const int _dev=0): N(_N){
      for(auto& p:_mu.irreps)
	parts[p.first.lambda]=new SnMultiPart(_N,p.first,p.second,fill,_dev);
      //parts.push_back(new SnMultiPart(_N,p.first,p.second,fill,_dev));
    }
    */


  public: // ---- Named constructors -------------------------------------------------------------------------
  
  
  static SnMultiVec zero(int _n, const SnType& _type, const int _dev=0){
    return SnMultiVec(_n,_type,cnine::fill::zero,_dev);
  }

    static SnMultiVec identity(int _n, const SnType& _type, const int _dev=0){
      return SnMultiVec(_n,_type,cnine::fill::identity,_dev);
    }

    static SnMultiVec gaussian(int _n, const SnType& _type, const int _dev=0){
      return SnMultiVec(_n,_type,cnine::fill::gaussian,_dev);
    }


  public: // ---- Access -------------------------------------------------------------------------------------

  
    SnMultiPart& operator[](const IntegerPartition& lambda) const{
      if(parts.find(lambda)==parts.end()) cerr<<"SnMultiPart not found"<<endl;
      return *parts[lambda];
    }
    

  public: // ---- Group actions ------------------------------------------------------------------------------


    SnMultiVec& apply_inplace(int i, const SnElement& sigma){
      for(auto p:parts)
	p.second->apply_inplace(i,sigma);
      return *this;
    }

    SnMultiVec& apply_inplace(int i, ContiguousCycle& cyc){
      for(auto p:parts)
	p.second->apply_inplace(i,cyc);
      return *this;
    }


  public: // ---- Fourier transforms -------------------------------------------------------------------------


    SnMultiVec(const SnFunction& f): N(f.N){
      parts[IntegerPartition({1})]=new SnMultiPart(f);
    }

    SnMultiVec uptransform() const{
      assert(parts.size()>0);
      int n=0;
      for(auto& p:parts){
	n=p.second->irrep->n+1;
	break;
      }
      Sn G(n);
      G.all_irreps();
      int newN=N/n;
      SnMultiVec R(newN);

      for(auto& p:G.obj->irrep_map){

	SnIrrepObj& irrep=*p.second;
	G.obj->make_ancestors(irrep);
	cout<<" "<<irrep.lambda<<endl;

	int m=0; 
	for(auto q: irrep.ancestors)
	  m+=(*this)[q->lambda].n;

	cout<<"N="<<N<<endl;
	SnMultiPart P(N,SnIrrep(&irrep),m, cnine::fill::zero);
	//cout<<P.dev<<endl;

	int I=0;
	int J=0;
	for(auto q: irrep.ancestors){
	  const SnMultiPart& sub=(*this)[q->lambda];
	  P.add_to_block_multi(I,J,sub);
	  I+=sub.dim(0);
	  J+=sub.n;
	}

	int M=P.dim(1);
	int stride=M/newN; 
	int substride=stride/n;
	for(int i=0; i<n; i++)
	  p.second->apply_left(P,ContiguousCycle(n-i,n-1),i*substride,(i+1)*substride,stride);

	cout<<14<<endl;
	P.reshape({P.dim(1),newN,n,substride});
	rtensor S=P; //.collapse(2); // <- TODO
	cout<<15<<endl;
	S.reshape({P.dim(1),newN*substride});
	cout<<16<<endl;

	R.parts[irrep.lambda]=new SnMultiPart(newN,&irrep,S);
      }
      return R;
    }


  public: // ---- I/O -----------------


    string str(string indent="") const{
      ostringstream oss;
      for(auto p:parts){
	oss<<*p.second<<endl;
      }
      return oss.str();
    }

    friend ostream& operator<<(ostream& stream, const SnMultiVec& x){
      stream<<x.str(); return stream;
    }

  };

}

#endif
