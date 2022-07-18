
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef _SnMultiPart
#define _SnMultiPart

#include "SnIrrep.hpp"
#include "SnPart.hpp"
#include "SnFunction.hpp"
#include "SnOverSmFunction.hpp"


namespace Snob2{

  typedef cnine::RtensorObj rtensor;


  class SnMultiPart: private rtensor{
  public:

    int N;
    SnIrrepObj const* irrep;


  public:


    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnMultiPart(const int _N, const SnIrrepObj* _irrep, const int _m, const FILLTYPE& fill, const int _dev=0): N(_N),
      rtensor(cnine::dims(_irrep->d,_N,_m),fill,_dev), irrep(_irrep){}
    
    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnMultiPart(const int _N, const IntegerPartition& _lambda, const int _m, const FILLTYPE& fill, const int _dev=0): 
      N(_N),
      rtensor(cnine::dims(_snbank->get_irrep(_lambda)->d,_N,_m),fill,_dev), 
      irrep(_snbank->get_irrep(_lambda)){}
    

  public: // ---- Named constructors -------------------------------------------------------------------------


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


    SnMultiPart(const SnFunction& f): 
      rtensor(f){
      N=f.N;
      reshape({1,N,1});
      irrep=_snbank->get_irrep({1});
    }

    SnMultiPart(const SnOverSmFunction& f): 
      rtensor(f){
      N=f.getN();
      reshape({1,N,1});
      irrep=_snbank->get_irrep({1});
    }

    SnFunction as_function(const int _n) const{
      int m=getm();
      const_cast<SnMultiPart&>(*this).reshape({dims(0)*N*getm()});
      SnFunction f(_n,*this);
      const_cast<SnMultiPart&>(*this).reshape({1,N,m});
      return f;
    }

    SnOverSmFunction as_function(const int _n, const int _m) const{
      int m=getm();
      int N=getN();
      const_cast<SnMultiPart&>(*this).reshape({dims(0)*N*m});
      SnOverSmFunction f(_n,_m,*this);
      const_cast<SnMultiPart&>(*this).reshape({1,N,m});
      return f;
    }

    /*
    SnFunction as_functn(const int _n) const{
      int m=getm();
      const_cast<SnMultiPart&>(*this).reshape({dims(0)*N*getm()});
      SnFunction f(_n,*this);
      const_cast<SnMultiPart&>(*this).reshape({1,N,m});
      return f;
    }
    */

    SnMultiPart(const SnPart& x): rtensor(x){
      N=1;
      irrep=x.irrep;
      reshape({dims(0),1,dims(1)});
    }


    operator SnPart() const &{
      assert(N==1);
      rtensor M(*this);
      M.reshape({dims(0),N*getm()});
      return SnPart(irrep,std::move(M));
    }

    operator SnPart() &&{
      assert(N==1);
      reshape({dims(0),N*getm()});
      return SnPart(irrep,std::move(*this));
    }


  public: // ---- Access -------------------------------------------------------------------------------------


    int getn() const{
      return irrep->lambda.getn();
    }

    int getN() const{
      return N;
    }

    int getm() const{
      return dims(2);
    }

   int getd() const{
      return dims(0);
    }

    IntegerPartition get_lambda() const{
      return irrep->lambda;
    }

    IntegerPartition key() const{
      return irrep->lambda;
    }

      
  public: // ---- Operations ---------------------------------------------------------------------------------


    void set_block_multi(const int ioffs, const int joffs, const SnMultiPart& M){
      view3().fuse01().block(ioffs*N,joffs,M.dim(0)*M.dim(1),M.dim(2)).set(M.view3().fuse01());
    }

    void add_to_block_multi(const int ioffs, const int joffs, const SnMultiPart& M){
      //block3(ioffs,0,joffs,M.dim(0),M.dim(1),M.dim(2)).set(M.view3());
      view3().fuse01().block(ioffs*N,joffs,M.dim(0)*M.dim(1),M.dim(2)).add(M.view3().fuse01());
      /*
      int m=getm();
      int subm=M.getm();
      int I=M.dim(0);
      for(int s=0; s<N; s++)
	for(int i=0; i<I; i++)
	  for(int j=0; j<subm; j++)
	    inc(i+ioffs,s,j+joffs,M.get_value(i,s,j));
      */
    }

    void add_block_to_multi(const int ioffs, const int joffs, SnMultiPart& M, float c=1.0) const{
      assert(getN()==M.getN());
      int I=M.dim(0);
      int J=M.getm();
      M.view3().fuse01().add(view3().fuse01().block(ioffs*N,joffs,M.dim(0)*N,M.dim(2)),c);
      /*
      for(int s=0; s<N; s++)
	for(int i=0; i<I; i++)
	  for(int j=0; j<J; j++)
	    M.inc(i,s,j,get_value(i+ioffs,s,j+joffs)*c);
      */
    }
 
    /*
    void add_to_block_block(const int ioffs, const int joffs, const rtensor& M, 
      const int io, const int jo, const int I, const int J){
      for(int i=0; i<I; i++)
	for(int j=0; j<J; j++)
	  inc(i+ioffs,j+joffs,M.get_value(i+io,j+jo));
    }
    */

    SnMultiPart reduce(){
      int n=getn();
      int newN=N/n;
      int m=getm();
      int I=dim(0);
      //cout<<"Reducing "<<endl<<*this<<"."<<endl;
      //cout<<n<<newN<<m<<endl;
      SnMultiPart R(newN,irrep,getm(),cnine::fill::zero,dev);
      split1(view3(),newN,n).reduce2_destructively_into(R.view3());
      /*
      for(int s=0; s<newN; s++)
	for(int t=0; t<n; t++)
	  for(int i=0; i<I; i++)
	    for(int j=0; j<m; j++)
	      R.inc(i,s,j,get_value(i,(s*n+t),j));
      */
      return R;
    }


    SnMultiPart broadcast(const int _N){
      int newN=N*_N;
      int m=getm();
      int I=dim(0);
      SnMultiPart R(newN,irrep,getm(),cnine::fill::zero,dev);
      split1(R.view3(),N,_N).broadcast2(view3());
      /*
      for(int s=0; s<N; s++)
	for(int t=0; t<_N; t++)
	  for(int i=0; i<I; i++)
	    for(int j=0; j<m; j++)
	      R.inc(i,s*_N+t,j,get_value(i,s,j));
      */
      return R;
    }


  public: // ---- Group actions ------------------------------------------------------------------------------


    SnMultiPart apply(const SnElement& sigma, const int o, const int s=1){
      SnMultiPart R(*this);
      int m=getm();
      reshape({dims(0),N*m});
      irrep->apply_left(R,sigma,o*m,(o+s)*m);
      reshape({dims(0),N,m});
      return R;
    }

    SnMultiPart& apply_inplace(const SnElement& sigma, const int o, const int s=1){
      int m=getm();
      reshape({dims(0),N*m});
      irrep->apply_left(*this,sigma,o*m,(o+s)*m);
      reshape({dims(0),N,m});
      return *this;
    }

    SnMultiPart apply(const ContiguousCycle& cyc, const int o, const int s=1){
      SnMultiPart R(*this);
      int m=getm();
      reshape({dims(0),N*m});
      irrep->apply_left(R,cyc,o*m,(o+s)*m);
      reshape({dims(0),N,m});
      return R;
    }

    SnMultiPart& apply_inplace(const ContiguousCycle& cyc, const int o, const int s=1){
      int m=getm();
      reshape({dims(0),N*m});
      irrep->apply_left(*this,cyc,o*m,(o+s)*m);
      reshape({dims(0),N,m});
      return *this;
    }
    
    SnMultiPart& apply_inplace_inv(const ContiguousCycle& cyc, const int o, const int s=1){
      int m=getm();
      reshape({dims(0),N*m});
      irrep->apply_left_inv(*this,cyc,o*m,(o+s)*m);
      reshape({dims(0),N,m});
      return *this;
    }


  public: // ---- I/O ----------------------------------------------------------------------------------------


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
    /*
    static SnMultiPart zero(const int _N, const initializer_list<int> list, const int n, const int _dev=0){
      return SnMultiPart(_N,list,n,cnine::fill_zero(),_dev);}
    
    static SnMultiPart identity(const int _N, const initializer_list<int> list, const int n, const int _dev=0){
      return SnMultiPart(_N,list,n,cnine::fill_identity(),_dev);}
    
    static SnMultiPart gaussian(const int _N, const initializer_list<int> list, const int n, const int _dev=0){
      return SnMultiPart(_N,list,n,cnine::fill_gaussian(),_dev);}
    */
      
    /*
    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnMultiPart(const int _N, const initializer_list<int> list, const int _m, const FILLTYPE& fill, const int _dev=0):
      N(_N),
      rtensor(cnine::dims(_snbank->get_irrep(list)->d,_m*_N),fill,_dev), 
      irrep(_snbank->get_irrep(list)){}
    */

    /*
    SnMultiPart(const int _N, const SnIrrepObj* _irrep, const float val):
      N(_N),
      rtensor(cnine::dims(1,1)), irrep(_irrep){
      set_value(0,0,val);
    }
    */
    
    /*
    SnMultiPart(const SnIrrep& _irrep, const rtensor& x): 
      rtensor(x), irrep(_irrep.obj){}

    SnMultiPart(const SnIrrep& _irrep, rtensor&& x): 
      rtensor(std::move(x)), irrep(_irrep.obj){}

    SnMultiPart(const SnIrrepObj* _irrep, rtensor&& x): 
      rtensor(std::move(x)), irrep(_irrep){}
    */

