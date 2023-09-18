
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef _SnPartB
#define _SnPartB

#include "SnIrrep.hpp"


namespace Snob2{

  //typedef cnine::RtensorObj rtensor;


  class SnPartB: public rtensor{
  public:

    SnIrrepObj const* irrep;


  public:

    SnPartB():
      rtensor(), irrep(nullptr){}

    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnPartB(const initializer_list<int> list, const int n, const FILLTYPE& fill, const int _dev=0):
      rtensor(cnine::dims(1,_snbank->get_irrep(list)->d,n),fill,_dev), 
      irrep(_snbank->get_irrep(list)){}
    
    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnPartB(const SnIrrepObj* _irrep, const int n, const FILLTYPE& fill, const int _dev=0):
      rtensor(cnine::dims(1,_irrep->d,n),fill,_dev), irrep(_irrep){}
    
    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnPartB(const SnIrrep& _irrep, const int n, const FILLTYPE& fill, const int _dev=0):
      rtensor(cnine::dims(1,_irrep.obj->d,n),fill,_dev), irrep(_irrep.obj){}
    
    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnPartB(const IntegerPartition& _lambda, const int n, const FILLTYPE& fill, const int _dev=0):
      rtensor(cnine::dims(1,_snbank->get_Sn(_lambda.getn())->get_irrep(_lambda)->d,n),fill,_dev), 
      irrep(_snbank->get_Sn(_lambda.getn())->get_irrep(_lambda)){
    }

    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnPartB(const int b, const initializer_list<int> list, const int n, const FILLTYPE& fill, const int _dev=0):
      rtensor(cnine::dims(b,_snbank->get_irrep(list)->d,n),fill,_dev), 
      irrep(_snbank->get_irrep(list)){}
    
    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnPartB(const int b, const SnIrrepObj* _irrep, const int n, const FILLTYPE& fill, const int _dev=0):
      rtensor(cnine::dims(b,_irrep->d,n),fill,_dev), irrep(_irrep){}
    
    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnPartB(const int b, const SnIrrep& _irrep, const int n, const FILLTYPE& fill, const int _dev=0):
      rtensor(cnine::dims(b,_irrep.obj->d,n),fill,_dev), irrep(_irrep.obj){}
    
    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnPartB(const int b, const IntegerPartition& _lambda, const int n, const FILLTYPE& fill, const int _dev=0):
      rtensor(cnine::dims(b,_snbank->get_Sn(_lambda.getn())->get_irrep(_lambda)->d,n),fill,_dev), 
      irrep(_snbank->get_Sn(_lambda.getn())->get_irrep(_lambda)){
    }


    SnPartB(const IntegerPartition& _lambda, const int n, const int _dev=0):
      SnPartB(1,_lambda,n,cnine::fill_raw(),_dev){}

    SnPartB(const SnIrrepObj* _irrep, const float val):
      rtensor(1, cnine::dims(1,1)), irrep(_irrep){
      set_value(0,0,val);
    }
    
    SnPartB(const int b, const IntegerPartition& _lambda, const int n, const int _dev=0):
      SnPartB(b,_lambda,n,cnine::fill_raw(),_dev){}

    SnPartB(const int b, const SnIrrepObj* _irrep, const float val):
      rtensor(b, cnine::dims(1,1)), irrep(_irrep){
      set_value(0,0,val);
    }
    

  public: // ---- named constructors ----


    static SnPartB raw(const initializer_list<int> list, const int n, const int _dev=0){
      return SnPartB(list,n,cnine::fill_raw(),_dev);}
    
    static SnPartB zero(const initializer_list<int> list, const int n, const int _dev=0){
      return SnPartB(list,n,cnine::fill_zero(),_dev);}
    
    static SnPartB identity(const initializer_list<int> list, const int n, const int _dev=0){
      return SnPartB(list,n,cnine::fill_identity(),_dev);}
    
    static SnPartB gaussian(const initializer_list<int> list, const int n, const int _dev=0){
      return SnPartB(list,n,cnine::fill_gaussian(),_dev);}


    static SnPartB raw(const IntegerPartition& _lambda, const int n, const int _dev=0){
      return SnPartB(_lambda,n,cnine::fill_raw(),_dev);}
    
    static SnPartB zero(const IntegerPartition& _lambda, const int n, const int _dev=0){
      return SnPartB(_lambda,n,cnine::fill_zero(),_dev);}
    
    static SnPartB identity(const IntegerPartition& _lambda, const int n, const int _dev=0){
      return SnPartB(_lambda,n,cnine::fill_identity(),_dev);}
    
    static SnPartB gaussian(const IntegerPartition& _lambda, const int n, const int _dev=0){
      return SnPartB(_lambda,n,cnine::fill_gaussian(),_dev);}


    static SnPartB raw(const SnIrrep& _rho, const int n, const int _dev=0){
      return SnPartB(_rho,n,cnine::fill_raw(),_dev);}
    
    static SnPartB zero(const SnIrrep& _rho, const int n, const int _dev=0){
      return SnPartB(_rho,n,cnine::fill_zero(),_dev);}
    
    static SnPartB identity(const SnIrrep& _rho, const int n, const int _dev=0){
      return SnPartB(_rho,n,cnine::fill_identity(),_dev);}
    
    static SnPartB gaussian(const SnIrrep& _rho, const int n, const int _dev=0){
      return SnPartB(_rho,n,cnine::fill_gaussian(),_dev);}



    static SnPartB raw(const int b, const initializer_list<int> list, const int n, const int _dev=0){
      return SnPartB(b,list,n,cnine::fill_raw(),_dev);}
    
    static SnPartB zero(const int b, const initializer_list<int> list, const int n, const int _dev=0){
      return SnPartB(b,list,n,cnine::fill_zero(),_dev);}
    
    static SnPartB identity(const int b, const initializer_list<int> list, const int n, const int _dev=0){
      return SnPartB(b,list,n,cnine::fill_identity(),_dev);}
    
    static SnPartB gaussian(const int b, const initializer_list<int> list, const int n, const int _dev=0){
      return SnPartB(b,list,n,cnine::fill_gaussian(),_dev);}


    static SnPartB raw(const int b, const IntegerPartition& _lambda, const int n, const int _dev=0){
      return SnPartB(b,_lambda,n,cnine::fill_raw(),_dev);}
    
    static SnPartB zero(const int b, const IntegerPartition& _lambda, const int n, const int _dev=0){
      return SnPartB(b,_lambda,n,cnine::fill_zero(),_dev);}
    
    static SnPartB identity(const int b, const IntegerPartition& _lambda, const int n, const int _dev=0){
      return SnPartB(b,_lambda,n,cnine::fill_identity(),_dev);}
    
    static SnPartB gaussian(const int b, const IntegerPartition& _lambda, const int n, const int _dev=0){
      return SnPartB(b,_lambda,n,cnine::fill_gaussian(),_dev);}


    static SnPartB raw(const int b, const SnIrrep& _rho, const int n, const int _dev=0){
      return SnPartB(b,_rho,n,cnine::fill_raw(),_dev);}
    
    static SnPartB zero(const int b, const SnIrrep& _rho, const int n, const int _dev=0){
      return SnPartB(b,_rho,n,cnine::fill_zero(),_dev);}
    
    static SnPartB identity(const int b, const SnIrrep& _rho, const int n, const int _dev=0){
      return SnPartB(b,_rho,n,cnine::fill_identity(),_dev);}
    
    static SnPartB gaussian(const int b, const SnIrrep& _rho, const int n, const int _dev=0){
      return SnPartB(b,_rho,n,cnine::fill_gaussian(),_dev);}


  public: // ---- Copying -----------------------------------------------------------------------------------


    SnPartB(const SnPartB& x):
      rtensor(x), irrep(x.irrep){}

    SnPartB(SnPartB&& x):
      rtensor(std::move(x)), irrep(x.irrep){}

    SnPartB& operator=(const SnPartB& x){
      rtensor::operator=(x);
      irrep=x.irrep;
      return *this;
    }

    SnPartB& operator=(SnPartB&& x){
      rtensor::operator=(std::move(x));
      irrep=x.irrep;
      return *this;
    }


  public: // ---- Conversions --------------------------------------------------------------------------------


    SnPartB(const SnIrrep& _irrep, const rtensor& x): 
      rtensor(x), irrep(_irrep.obj){
      SNOB2_COPY_WARNING();
    }

    SnPartB(const SnIrrep& _irrep, rtensor&& x): 
      rtensor(std::move(x)), irrep(_irrep.obj){
      SNOB2_MOVE_WARNING();
    }

    SnPartB(const SnIrrepObj* _irrep, const rtensor& x): 
      rtensor(x), irrep(_irrep){
      SNOB2_COPY_WARNING();
      //cout<<"copy!"<<endl;
   }

    SnPartB(const SnIrrepObj* _irrep, rtensor&& x): 
      rtensor(std::move(x)), irrep(_irrep){
      SNOB2_MOVE_WARNING();
      //cout<<"move!"<<endl;
   }


  public: // ---- Access -------------------------------------------------------------------------------------


    int getn() const{
      return irrep->lambda.getn();
    }

    SnIrrep get_rho() const{
      return irrep;
    }

    IntegerPartition get_lambda() const{
      return irrep->lambda;
    }

    IntegerPartition key() const{
      return irrep->lambda;
    }

    int getb() const{
      return dims(0);
    }
    
    int getm() const{
      return dims(2);
    }

   int getd() const{
      return dims(1);
    }

      
  public: // ---- Operations ---------------------------------------------------------------------------------


    /*
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
    */

    /*
    SnPartB operator*(const float c) const{
      rtensor M(dims,cnine::fill::zero,dev);
      M.add(*this,c);
      return SnPartB(irrep,std::move(M));
    }
    */


  public:


    SnPartB apply(const SnElement& sigma) const{
      SnPartB R(*this);
      irrep->apply(R.view3(),sigma);
      return R;
    }

    SnPartB& apply_inplace(const SnElement& sigma){
      irrep->apply(view3(),sigma);
      return *this;
    }

    SnPartB apply(const ContiguousCycle& cyc) const{
      SnPartB R(*this);
      irrep->apply(R.view3(),cyc);
      return R;
    }

    SnPartB& apply_inplace(const ContiguousCycle& cyc){
      irrep->apply(view3(),cyc);
      return *this;
    }

    SnPartB apply(const Transposition& x) const{
      SnPartB R(*this);
      irrep->apply(R.view3(),x);
      return R;
    }


  public:

    string str(string indent="") const{
      return indent+"Part "+irrep->lambda.str()+":\n"+rtensor::str(indent);
    }

    friend ostream& operator<<(ostream& stream, const SnPartB& x){
      stream<<x.str(); return stream;
    }


  };


  inline SnPartB operator*(const SnElement& sigma, const SnPartB& A){
    return A.apply(sigma);
  }

  inline int sameb(const SnPartB& x, const SnPartB& y){
    assert(x.getb()==y.getb());
    return x.getb();
  }


}

#endif
