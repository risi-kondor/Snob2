#ifndef _SnMultiPart
#define _SnMultiPart

#include "SnIrrep.hpp"
#include "FunctionOnGroup.hpp"
#include "SnPart.hpp"

namespace Snob2{

  typedef cnine::RtensorObj rtensor;


  class SnMultiPart: public rtensor{
  public:

    int N;
    int n;

    SnIrrepObj const* irrep;

    bool is_view=false;


  public:

    SnMultiPart(int _N, const SnIrrep& _irrep, const int _n, const int _dev=0):
      rtensor(cnine::dims(_irrep.obj->d,_N*_n),cnine::fill::raw,dev), irrep(_irrep.obj), N(_N), n(_n){}

    SnMultiPart(int _N, const IntegerPartition& _lambda, const int _n, const int _dev=0):
      rtensor(cnine::dims(_snbank->get_Sn(_lambda.getn())->get_irrep(_lambda)->d,_N*_n),cnine::fill::raw,dev), 
      irrep(_snbank->get_Sn(_lambda.getn())->get_irrep(_lambda)), N(_N), n(_n){}

    template<typename FILLTYPE>
    SnMultiPart(int _N, const SnIrrep& _irrep, const int _n, const FILLTYPE& fill, const int _dev=0):
      rtensor(cnine::dims(_irrep.obj->d,_N*_n),fill,dev), irrep(_irrep.obj), N(_N), n(_n){}
    
    template<typename FILLTYPE>
    SnMultiPart(int _N, const IntegerPartition& _lambda, const int _n, const FILLTYPE& fill, const int _dev=0):
      rtensor(cnine::dims(_snbank->get_Sn(_lambda.getn())->get_irrep(_lambda)->d,_N*_n),fill,dev), 
      irrep(_snbank->get_Sn(_lambda.getn())->get_irrep(_lambda)), N(_N), n(_n){}


  public: // ---- named constructors ----


    static SnMultiPart zero(int N, const IntegerPartition& _lambda, const int n, const int _dev=0){
      return SnMultiPart(N,_lambda,n,cnine::fill_zero(),_dev);}
    
    static SnMultiPart identity(int N, const IntegerPartition& _lambda, const int n, const int _dev=0){
      return SnMultiPart(N,_lambda,n,cnine::fill_identity(),_dev);}
    
    static SnMultiPart gaussian(int N, const IntegerPartition& _lambda, const int n, const int _dev=0){
      return SnMultiPart(N,_lambda,n,cnine::fill_gaussian(),_dev);}


    static SnMultiPart zero(int N, const SnIrrep& _rho, const int n, const int _dev=0){
      return SnMultiPart(N,_rho,n,cnine::fill_zero(),_dev);}
    
    static SnMultiPart identity(int N, const SnIrrep& _rho, const int n, const int _dev=0){
      return SnMultiPart(N,_rho,n,cnine::fill_identity(),_dev);}
    
    static SnMultiPart gaussian(int N, const SnIrrep& _rho, const int n, const int _dev=0){
      return SnMultiPart(N,_rho,n,cnine::fill_gaussian(),_dev);}


  public: // ---- Conversions --------------------------------------------------------------------------------


    SnMultiPart(const int _N, const SnIrrep& _irrep, const rtensor& x): 
      rtensor(x), irrep(_irrep.obj), N(_N), n(x.dim(1)/_N){}

    SnMultiPart(const int _N, const SnIrrep& _irrep, rtensor&& x): 
      rtensor(std::move(x)), irrep(_irrep.obj), N(_N), n(x.dim(1)/_N){}

    SnMultiPart(const int _N, const SnIrrepObj* _irrep, const rtensor& x): 
      rtensor(x), irrep(_irrep), N(_N), n(x.dim(1)/_N){}

    SnMultiPart(const int _N, const SnIrrepObj* _irrep, rtensor&& x): 
      rtensor(std::move(x)), irrep(_irrep), N(_N), n(x.dim(1)/_N){}


  public: // ---- Operations ---------------------------------------------------------------------------------


    void add_to_block_multi(const int ioffs, const int joffs, const SnMultiPart& x){
      cout<<x.N<<" "<<N<<endl;
      SNOB2_ASSERT(x.N==N,"Mismatch in multi dimension");
      int I=x.dim(0);
      int J=x.n;
      for(int c=0; c<N; c++)
	for(int i=0; i<I; i++)
	  for(int j=0; j<J; j++){}
	    //inc(ioffs+i,c*n+joffs*j,x(i,c*x.n+j));
    }


  public: // ---- Fourier transforms ------------------


    SnMultiPart(const SnFunction& f): // TODO: eliminate copying
      rtensor(f), irrep(_snbank->get_irrep(IntegerPartition({1}))){
      N=f.dim(0);
      n=1;
      reshape({1,N});
    }

    operator SnPart() const{
      return SnPart(SnIrrep(irrep),*this);
    }


  public:

    /*
    SnMultiPart apply(const int i, const SnElement& sigma) const{
      SnMultiPart R(*this);
      irrep->apply_left(R,sigma,i*n,i*n+n);
      return R;
    }
    */

    SnMultiPart& apply_inplace(const int i, const SnElement& sigma){
      irrep->apply_left(*this,sigma,i*n,i*n+n);
      return *this;
    }

    /*
    SnMultiPart apply(const int i, const ContiguousCycle& cyc) const{
      SnMultiPart R(*this);
      irrep->apply_left(R,cyc,i*n,i*n+n);
      return R;
    }
    */

    SnMultiPart& apply_inplace(const int i, const ContiguousCycle& cyc){
      irrep->apply_left(*this,cyc,i*n,i*n+n);
      return *this;
    }


  public:

    string str(string indent="") const{
      return "SnMultiPart("+irrep->lambda.str()+")\n"+rtensor::str();
    }

    friend ostream& operator<<(ostream& stream, const SnMultiPart& x){
      stream<<x.str(); return stream;
    }


  };

}

#endif
