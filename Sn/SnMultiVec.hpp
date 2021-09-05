#ifndef _SnMultiVec
#define _SnMultiVec

#include "SnMultiPart.hpp"
#include "SnType.hpp"

namespace Snob2{

  typedef cnine::RtensorObj rtensor;


  class SnMultiVec{
  public:

    int N;

    vector<SnMultiPart*> parts;

    ~SnMultiVec(){
      for(auto p:parts) delete p;
    }


  public:

    SnMultiVec(){}

    template<typename FILLTYPE>
    SnMultiVec(int _N, const SnType& _type, const FILLTYPE& fill, const int _dev=0): N(_N){
      for(auto& p:_type.map)
	parts.push_back(new SnMultiPart(_N,p.first,p.second,fill,_dev));
      //parts.push_back(new SnPart(p.first,p.second,fill,_dev));
    }

    template<typename FILLTYPE>
    SnMultiVec(int _N, const SnRepresentation& _mu, const FILLTYPE& fill, const int _dev=0): N(_N){
      for(auto& p:_mu.irreps)
	parts.push_back(new SnMultiPart(_N,p.first,p.second,fill,_dev));
      //parts.push_back(new SnPart(p.first,p.second,fill,_dev));
    }


  public:

    static SnMultiVec zero(int _n, const SnType& _type, const int _dev=0){
      return SnMultiVec(_n,_type,cnine::fill::zero,_dev);
    }

    static SnMultiVec identity(int _n, const SnType& _type, const int _dev=0){
      return SnMultiVec(_n,_type,cnine::fill::identity,_dev);
    }

    static SnMultiVec gaussian(int _n, const SnType& _type, const int _dev=0){
      return SnMultiVec(_n,_type,cnine::fill::gaussian,_dev);
    }


  public:

    SnMultiVec& apply_inplace(int i, const SnElement& sigma){
      for(auto p:parts)
	p->apply_inplace(i,sigma);
      return *this;
    }

    SnMultiVec& apply_inplace(int i, ContiguousCycle& cyc){
      for(auto p:parts)
	p->apply_inplace(i,cyc);
      return *this;
    }


  public: // ---- Fourier transforms ------------------


    SnMultiVec(const FunctionOnGroup<Sn,rtensor>& f): N(f.G.getn()){
      parts.push_back(new SnMultiPart(f));
    }

    SnMultiVec* uptransform() const{
      assert(parts.size()>0);
      int n=parts[0]->irrep->n;
      int newN=N/n;
      Sn G(n);
      SnMultiVec* R=new SnMultiVec(newN,Sn(n).repr(),cnine::fill_zero());
      return R;
    }


  public: // ---- I/O -----------------


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

}

#endif
