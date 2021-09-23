#ifndef _SnMultiPart
#define _SnMultiPart

#include "SnIrrep.hpp"
//#include "SnMultiPart.hpp"
#include "SnFunction.hpp"


namespace Snob2{

  typedef cnine::RtensorObj rtensor;


  class SnMultiPart: public rtensor{
  public:

    int N;
    SnIrrepObj const* irrep;


  public:


    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnMultiPart(const int _N, const initializer_list<int> list, const int n, const FILLTYPE& fill, const int _dev=0):
      N(_N),
      rtensor(cnine::dims(_snbank->get_irrep(list)->d,n),fill,_dev), 
      irrep(_snbank->get_irrep(list)){}
    
    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnMultiPart(const int _N, const SnIrrepObj* _irrep, const int n, const FILLTYPE& fill, const int _dev=0):
      N(_N),
      rtensor(cnine::dims(_irrep->d,n),fill,_dev), irrep(_irrep){}
    
    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnMultiPart(const int _N, const IntegerPartition& _lambda, const int n, const FILLTYPE& fill, const int _dev=0):
      N(_N),
      rtensor(cnine::dims(_snbank->get_Sn(_lambda.getn())->get_irrep(_lambda)->d,n),fill,_dev), 
      irrep(_snbank->get_Sn(_lambda.getn())->get_irrep(_lambda)){
    }


    SnMultiPart(const int _N, const SnIrrepObj* _irrep, const float val):
      N(_N),
      rtensor(cnine::dims(1,1)), irrep(_irrep){
      set_value(0,0,val);
    }
    
    SnMultiPart(const SnFunction& f): 
      SnMultiPart(f.N,IntegerPartition({1}),f.n,cnine::fill::raw){}
    

  public: // ---- named constructors ----


    static SnMultiPart zero(const int _N, const initializer_list<int> list, const int n, const int _dev=0){
      return SnMultiPart(_N,list,n,cnine::fill_zero(),_dev);}
    
    static SnMultiPart identity(const int _N, const initializer_list<int> list, const int n, const int _dev=0){
      return SnMultiPart(_N,list,n,cnine::fill_identity(),_dev);}
    
    static SnMultiPart gaussian(const int _N, const initializer_list<int> list, const int n, const int _dev=0){
      return SnMultiPart(_N,list,n,cnine::fill_gaussian(),_dev);}


    static SnMultiPart zero(const int _N, const IntegerPartition& _lambda, const int n, const int _dev=0){
      return SnMultiPart(_N,_lambda,n,cnine::fill_zero(),_dev);}
    
    static SnMultiPart identity(const int _N, const IntegerPartition& _lambda, const int n, const int _dev=0){
      return SnMultiPart(_N,_lambda,n,cnine::fill_identity(),_dev);}
    
    static SnMultiPart gaussian(const int _N, const IntegerPartition& _lambda, const int n, const int _dev=0){
      return SnMultiPart(_N,_lambda,n,cnine::fill_gaussian(),_dev);}


  public: // ---- Copying -----------------------------------------------------------------------------------


    SnMultiPart(const SnMultiPart& x):
      N(x.N),rtensor(x), irrep(x.irrep){}

    SnMultiPart(SnMultiPart&& x):
      N(x.N),rtensor(std::move(x)), irrep(x.irrep){}

    SnMultiPart& operator=(const SnMultiPart& x){
      N=x.N;
      rtensor::operator=(x);
      irrep=x.irrep;
      return *this;
    }

    SnMultiPart& operator=(SnMultiPart&& x){
      N=x.N;
      rtensor::operator=(std::move(x));
      irrep=x.irrep;
      return *this;
    }


  public: // ---- Conversions --------------------------------------------------------------------------------


    SnMultiPart(const SnIrrep& _irrep, const rtensor& x): 
      rtensor(x), irrep(_irrep.obj){}

    SnMultiPart(const SnIrrep& _irrep, rtensor&& x): 
      rtensor(std::move(x)), irrep(_irrep.obj){}

    SnMultiPart(const SnIrrepObj* _irrep, rtensor&& x): 
      rtensor(std::move(x)), irrep(_irrep){}


  public: // ---- Access -------------------------------------------------------------------------------------


    int getn() const{
      return irrep->lambda.getn();
    }

    IntegerPartition get_lambda() const{
      return irrep->lambda;
    }

    IntegerPartition key() const{
      return irrep->lambda;
    }

    int getm() const{
      return dims(1);
    }

   int getd() const{
      return dims(0);
    }

      
  public: // ---- Operations ---------------------------------------------------------------------------------


    void add_to_block(const int ioffs, const int joffs, const rtensor& M){
      int I=M.dim(0);
      int J=M.dim(1);
      for(int i=0; i<I; i++)
	for(int j=0; j<J; j++)
	  inc(i+ioffs,j+joffs,M.get_value(i,j));
    }
    
    void add_block_to(const int ioffs, const int joffs, rtensor& M, float c=1.0) const{
      int I=M.dim(0);
      int J=M.dim(1);
      for(int i=0; i<I; i++)
	for(int j=0; j<J; j++)
	  M.inc(i,j,get_value(i+ioffs,j+joffs)*c);
    }
 
    void add_to_block_block(const int ioffs, const int joffs, const rtensor& M, 
      const int io, const int jo, const int I, const int J){
      for(int i=0; i<I; i++)
	for(int j=0; j<J; j++)
	  inc(i+ioffs,j+joffs,M.get_value(i+io,j+jo));
    }
 
    /*
    SnMultiPart operator*(const float c) const{
      rtensor M(dims,cnine::fill::zero,dev);
      M.add(*this,c);
      return SnMultiPart(irrep,std::move(M));
    }
    */


  public:


    /*
    SnMultiPart apply(const SnElement& sigma) const{
      SnMultiPart R(*this);
      irrep->apply_left(R,sigma);
      return R;
    }

    SnMultiPart& apply_inplace(const SnElement& sigma){
      irrep->apply_left(*this,sigma);
      return *this;
    }

    SnMultiPart apply(const ContiguousCycle& cyc) const{
      SnMultiPart R(*this);
      irrep->apply_left(R,cyc);
      return R;
    }

    SnMultiPart& apply_inplace(const ContiguousCycle& cyc){
      irrep->apply_left(*this,cyc);
      return *this;
    }

    SnMultiPart& apply_inplace_inv(const ContiguousCycle& cyc){
      irrep->apply_left_inv(*this,cyc);
      return *this;
    }
    */

  public:

    string str(string indent="") const{
      return "MultiPart "+irrep->lambda.str()+":\n"+rtensor::str();
    }

    friend ostream& operator<<(ostream& stream, const SnMultiPart& x){
      stream<<x.str(); return stream;
    }


  };


  //inline SnMultiPart operator*(const SnElement& sigma, const SnMultiPart& A){
  //return A.apply(sigma);
  //}


}

#endif
