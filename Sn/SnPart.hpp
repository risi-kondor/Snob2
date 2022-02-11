
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


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


    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnPart(const initializer_list<int> list, const int n, const FILLTYPE& fill, const int _dev=0):
      rtensor(cnine::dims(_snbank->get_irrep(list)->d,n),fill,_dev), 
      irrep(_snbank->get_irrep(list)){}
    
    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnPart(const SnIrrepObj* _irrep, const int n, const FILLTYPE& fill, const int _dev=0):
      rtensor(cnine::dims(_irrep->d,n),fill,_dev), irrep(_irrep){}
    
    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnPart(const SnIrrep& _irrep, const int n, const FILLTYPE& fill, const int _dev=0):
      rtensor(cnine::dims(_irrep.obj->d,n),fill,_dev), irrep(_irrep.obj){}
    
    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnPart(const IntegerPartition& _lambda, const int n, const FILLTYPE& fill, const int _dev=0):
      rtensor(cnine::dims(_snbank->get_Sn(_lambda.getn())->get_irrep(_lambda)->d,n),fill,_dev), 
      irrep(_snbank->get_Sn(_lambda.getn())->get_irrep(_lambda)){
    }


    SnPart(const IntegerPartition& _lambda, const int n, const int _dev=0):
      SnPart(_lambda,n,cnine::fill_raw(),_dev){}

    SnPart(const SnIrrepObj* _irrep, const float val):
      rtensor(cnine::dims(1,1)), irrep(_irrep){
      set_value(0,0,val);
    }
    

  public: // ---- named constructors ----


    static SnPart raw(const initializer_list<int> list, const int n, const int _dev=0){
      return SnPart(list,n,cnine::fill_raw(),_dev);}
    
    static SnPart zero(const initializer_list<int> list, const int n, const int _dev=0){
      return SnPart(list,n,cnine::fill_zero(),_dev);}
    
    static SnPart identity(const initializer_list<int> list, const int n, const int _dev=0){
      return SnPart(list,n,cnine::fill_identity(),_dev);}
    
    static SnPart gaussian(const initializer_list<int> list, const int n, const int _dev=0){
      return SnPart(list,n,cnine::fill_gaussian(),_dev);}


    static SnPart raw(const IntegerPartition& _lambda, const int n, const int _dev=0){
      return SnPart(_lambda,n,cnine::fill_raw(),_dev);}
    
    static SnPart zero(const IntegerPartition& _lambda, const int n, const int _dev=0){
      return SnPart(_lambda,n,cnine::fill_zero(),_dev);}
    
    static SnPart identity(const IntegerPartition& _lambda, const int n, const int _dev=0){
      return SnPart(_lambda,n,cnine::fill_identity(),_dev);}
    
    static SnPart gaussian(const IntegerPartition& _lambda, const int n, const int _dev=0){
      return SnPart(_lambda,n,cnine::fill_gaussian(),_dev);}


    static SnPart raw(const SnIrrep& _rho, const int n, const int _dev=0){
      return SnPart(_rho,n,cnine::fill_raw(),_dev);}
    
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
      rtensor(x), irrep(_irrep.obj){
    }

    SnPart(const SnIrrep& _irrep, rtensor&& x): 
      rtensor(std::move(x)), irrep(_irrep.obj){
    }

    SnPart(const SnIrrepObj* _irrep, const rtensor& x): 
      rtensor(x), irrep(_irrep){
      //cout<<"copy!"<<endl;
   }

    SnPart(const SnIrrepObj* _irrep, rtensor&& x): 
      rtensor(std::move(x)), irrep(_irrep){
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
    SnPart operator*(const float c) const{
      rtensor M(dims,cnine::fill::zero,dev);
      M.add(*this,c);
      return SnPart(irrep,std::move(M));
    }
    */


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

    SnPart& apply_inplace_inv(const ContiguousCycle& cyc){
      irrep->apply_left_inv(*this,cyc);
      return *this;
    }

    SnPart apply(const Transposition& x) const{
      SnPart R(*this);
      irrep->apply_left(R,x);
      return R;
    }


  public:

    string str(string indent="") const{
      return "Part "+irrep->lambda.str()+":\n"+rtensor::str();
    }

    friend ostream& operator<<(ostream& stream, const SnPart& x){
      stream<<x.str(); return stream;
    }


  };


  inline SnPart operator*(const SnElement& sigma, const SnPart& A){
    return A.apply(sigma);
  }


}

#endif
