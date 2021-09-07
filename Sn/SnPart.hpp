#ifndef _SnPart
#define _SnPart

#include "SnIrrep.hpp"
//#include "SnMultiPart.hpp"

namespace Snob2{

  typedef cnine::RtensorObj rtensor;


  class SnPart: public rtensor{
  public:

    SnIrrepObj const* irrep;


  public:

    template<typename FILLTYPE>
    SnPart(const initializer_list<int> list, const int n, const FILLTYPE& fill, const int _dev=0):
      rtensor(cnine::dims(_snbank->get_irrep(list)->d,n),fill,dev), 
      irrep(_snbank->get_irrep(list)){}
    
    template<typename FILLTYPE>
    SnPart(const SnIrrepObj* _irrep, const int n, const FILLTYPE& fill, const int _dev=0):
      rtensor(cnine::dims(_irrep->d,n),fill,_dev), irrep(_irrep){
      //cout<<"        "<<dims<<endl;
      //cout<<rtensor::str()<<endl;
    }
    
    template<typename FILLTYPE>
    SnPart(const SnIrrep& _irrep, const int n, const FILLTYPE& fill, const int _dev=0):
      rtensor(cnine::dims(_irrep.obj->d,n),fill,dev), irrep(_irrep.obj){}
    
    template<typename FILLTYPE>
    SnPart(const IntegerPartition& _lambda, const int n, const FILLTYPE& fill, const int _dev=0):
      rtensor(cnine::dims(_snbank->get_Sn(_lambda.getn())->get_irrep(_lambda)->d,n),fill,dev), 
      irrep(_snbank->get_Sn(_lambda.getn())->get_irrep(_lambda)){}


    SnPart(const SnIrrepObj* _irrep, const float val):
      rtensor(cnine::dims(1,1)), irrep(_irrep){
      set_value(0,0,val);
    }
    

  public: // ---- named constructors ----


    static SnPart zero(const initializer_list<int> list, const int n, const int _dev=0){
      return SnPart(list,n,cnine::fill_zero(),_dev);}
    
    static SnPart identity(const initializer_list<int> list, const int n, const int _dev=0){
      return SnPart(list,n,cnine::fill_identity(),_dev);}
    
    static SnPart gaussian(const initializer_list<int> list, const int n, const int _dev=0){
      return SnPart(list,n,cnine::fill_gaussian(),_dev);}


    static SnPart zero(const IntegerPartition& _lambda, const int n, const int _dev=0){
      return SnPart(_lambda,n,cnine::fill_zero(),_dev);}
    
    static SnPart identity(const IntegerPartition& _lambda, const int n, const int _dev=0){
      return SnPart(_lambda,n,cnine::fill_identity(),_dev);}
    
    static SnPart gaussian(const IntegerPartition& _lambda, const int n, const int _dev=0){
      return SnPart(_lambda,n,cnine::fill_gaussian(),_dev);}


    static SnPart zero(const SnIrrep& _rho, const int n, const int _dev=0){
      return SnPart(_rho,n,cnine::fill_zero(),_dev);}
    
    static SnPart identity(const SnIrrep& _rho, const int n, const int _dev=0){
      return SnPart(_rho,n,cnine::fill_identity(),_dev);}
    
    static SnPart gaussian(const SnIrrep& _rho, const int n, const int _dev=0){
      return SnPart(_rho,n,cnine::fill_gaussian(),_dev);}


  public: // ---- Copying -----------------------------------------------------------------------------------


    SnPart(const SnPart& x):
      rtensor(x), irrep(x.irrep){}

    SnPart(SnPart&& x):
      rtensor(std::move(x)), irrep(x.irrep){}

    SnPart& operator=(const SnPart& x){
      rtensor::operator=(x);
      irrep=x.irrep;
      return *this;
    }

    SnPart& operator=(SnPart&& x){
      rtensor::operator=(std::move(x));
      irrep=x.irrep;
      return *this;
    }


  public: // ---- Conversions --------------------------------------------------------------------------------


    SnPart(const SnIrrep& _irrep, const rtensor& x): 
      rtensor(x), irrep(_irrep.obj){}

    SnPart(const SnIrrep& _irrep, rtensor&& x): 
      rtensor(std::move(x)), irrep(_irrep.obj){}

    SnPart(const SnIrrepObj* _irrep, rtensor&& x): 
      rtensor(std::move(x)), irrep(_irrep){}


  public:


    void add_to_block(const int ioffs, const int joffs, const rtensor& M){
      int I=M.dim(0);
      int J=M.dim(1);
      for(int i=0; i<I; i++)
	for(int j=0; j<J; j++)
	  inc(i+ioffs,j+joffs,M.get_value(i,j));
    }
    

  public:


    SnPart apply(const SnElement& sigma) const{
      SnPart R(*this);
      irrep->apply_left(R,sigma);
      return R;
    }

    SnPart& apply_inplace(const SnElement& sigma){
      irrep->apply_left(*this,sigma);
      return *this;
    }

    SnPart apply(const ContiguousCycle& cyc) const{
      SnPart R(*this);
      irrep->apply_left(R,cyc);
      return R;
    }

    SnPart& apply_inplace(const ContiguousCycle& cyc){
      irrep->apply_left(*this,cyc);
      return *this;
    }


  public:

    string str(string indent="") const{
      return "Part "+irrep->lambda.str()+":\n"+rtensor::str();
    }

    friend ostream& operator<<(ostream& stream, const SnPart& x){
      stream<<x.str(); return stream;
    }


  };

}

#endif
