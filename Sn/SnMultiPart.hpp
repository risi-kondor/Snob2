#ifndef _SnMultiPart
#define _SnMultiPart

#include "SnIrrep.hpp"
#include "SnPart.hpp"
#include "SnFunction.hpp"


namespace Snob2{

  typedef cnine::RtensorObj rtensor;


  class SnMultiPart: public rtensor{
  public:

    int N;
    SnIrrepObj const* irrep;


  public:


    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnMultiPart(const int _N, const initializer_list<int> list, const int _m, const FILLTYPE& fill, const int _dev=0):
      N(_N),
      rtensor(cnine::dims(_snbank->get_irrep(list)->d,_m*_N),fill,_dev), 
      irrep(_snbank->get_irrep(list)){}
    
    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnMultiPart(const int _N, const SnIrrepObj* _irrep, const int _m, const FILLTYPE& fill, const int _dev=0):
      N(_N),
      rtensor(cnine::dims(_irrep->d,_m*_N),fill,_dev), irrep(_irrep){}
    
    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnMultiPart(const int _N, const IntegerPartition& _lambda, const int _m, const FILLTYPE& fill, const int _dev=0):
      N(_N),
      rtensor(cnine::dims(_snbank->get_Sn(_lambda.getn())->get_irrep(_lambda)->d,_m*_N),fill,_dev), 
      irrep(_snbank->get_Sn(_lambda.getn())->get_irrep(_lambda)){
    }


    SnMultiPart(const int _N, const SnIrrepObj* _irrep, const float val):
      N(_N),
      rtensor(cnine::dims(1,1)), irrep(_irrep){
      set_value(0,0,val);
    }
    
    SnMultiPart(const SnFunction& f): 
      rtensor(f){
      N=f.N;
      reshape({1,N});
      irrep=_snbank->get_irrep({1});
    }
    

  public: // ---- Named constructors -------------------------------------------------------------------------


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


    operator SnPart() const{
      assert(N==1);
      return SnPart(irrep,*this);
    }


  public: // ---- Access -------------------------------------------------------------------------------------


    int getn() const{
      return irrep->lambda.getn();
    }

    int getN() const{
      return N;
    }

    IntegerPartition get_lambda() const{
      return irrep->lambda;
    }

    IntegerPartition key() const{
      return irrep->lambda;
    }

    int getm() const{
      return dims(1)/N;
    }

   int getd() const{
      return dims(0);
    }

      
  public: // ---- Operations ---------------------------------------------------------------------------------


    void add_to_block_multi(const int ioffs, const int joffs, const SnMultiPart& M){
      int m=getm();
      int subm=M.getm();
      //cout<<"m="<<m<<endl;
      //cout<<"add_to_block("<<ioffs<<joffs<<")"<<endl;
      int I=M.dim(0);
      for(int s=0; s<N; s++)
	for(int i=0; i<I; i++)
	  for(int j=0; j<subm; j++)
	    inc(i+ioffs,s*m+j+joffs,M.get_value(i,s*subm+j));
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

    SnMultiPart reduce(){
      int n=getn();
      int newN=N/n;
      int m=getm();
      int I=dim(0);
      //cout<<"Reducing "<<endl<<*this<<"."<<endl;
      //cout<<n<<newN<<m<<endl;
      SnMultiPart R(newN,irrep,getm(),cnine::fill::zero,dev);
      for(int s=0; s<newN; s++)
	for(int t=0; t<n; t++)
	  for(int i=0; i<I; i++)
	    for(int j=0; j<m; j++)
	      R.inc(i,s*m+j,get_value(i,(s*n+t)*m+j));
      return R;
    }


  public:


    /*
    SnMultiPart apply(const SnElement& sigma) const{
      SnMultiPart R(*this);
      irrep->apply_left(R,sigma);
      return R;
    }
    */

    SnMultiPart& apply_inplace(const SnElement& sigma, const int o, const int s=1){
      int m=getm();
      irrep->apply_left(*this,sigma,o*m,(o+s)*m);
      return *this;
    }

    /*
    SnMultiPart apply(const ContiguousCycle& cyc) const{
      SnMultiPart R(*this);
      irrep->apply_left(R,cyc);
      return R;
    }
    */

    SnMultiPart& apply_inplace(const ContiguousCycle& cyc, const int o, const int s=1){
      int m=getm();
      //cout<<" "<<irrep->lambda<<cyc<<endl;
      irrep->apply_left(*this,cyc,o*m,(o+s)*m);
      return *this;
    }
    
    /*
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
