#ifndef _SnMultiPart
#define _SnMultiPart

#include "SnIrrep.hpp"
#include "FunctionOnGroup.hpp"


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


  public: // ---- Fourier transforms ------------------


    SnMultiPart(const FunctionOnGroup<Sn,rtensor>& f): 
      rtensor(f), irrep(f.G.irrep(IntegerPartition({1})).obj){
      reshape(cnine::dims(1,dim(0)));
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
