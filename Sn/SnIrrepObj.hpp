
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef _SnIrrepObj
#define _SnIrrepObj

#include <cnine/containers>
//#include "associative_container.hpp"

#include "IntegerPartition.hpp"
#include "ContiguousCycle.hpp"
#include "RtensorObj.hpp"
#include "IntTensor.hpp"
#include "YoungTableau.hpp"
#include "SnElement.hpp"

#include "ScaleSomeSlicesFn.hpp"
#include "GivensSomeSlicesFn.hpp"

namespace Snob2{

  typedef cnine::RtensorObj rtensor;
  typedef cnine::IntTensor itensor;


  class SnIrrepObj{
  public:

    int n;
    int d;
    IntegerPartition lambda;
    vector<YoungTableau*> tableaux;
    mutable cnine::associative_container<int,rtensor> YJM;
    //vector<SnIrrepObj*> ancestors; 
    //vector<SnIrrepObj*> descendents;
    //SnClassFunction chi;

    mutable int* YORt=nullptr;
    mutable double* YOR1;
    mutable double* YOR2;

    mutable itensor* YORndiags=nullptr;
    mutable itensor* YORdiagIndices=nullptr;
    mutable rtensor* YORdiagCoeffs=nullptr;
    mutable itensor* YORgivensIndices=nullptr;
    mutable rtensor* YORgivensCoeffs=nullptr;


  public:

    SnIrrepObj(const IntegerPartition& _lambda):
      lambda(_lambda){
      tableaux=_combibank->get_YoungTableaux(lambda);
      d=tableaux.size();
      n=_lambda.getn();
    }

    ~SnIrrepObj(){
      delete[] YORt;
      delete[] YOR1;
      delete[] YOR2;
      delete YORndiags;
      delete YORdiagIndices;
      delete YORdiagCoeffs;
      delete YORgivensIndices;
      delete YORgivensCoeffs;
    }


  public:

    SnIrrepObj(const SnIrrepObj& x)=delete;

    SnIrrepObj& operator=(const SnIrrepObj& x)=delete;


  public: // ---- Access ------------------------------------------------------------------------------------ 

    
    int index(const YoungTableau& t) const {
      int i=0; for(auto p: tableaux) if(*p==t) return i; else i++; return -1;}


  public: // ---- Operations --------------------------------------------------------------------------------


    rtensor operator()(const SnElement& sigma) const{
      rtensor R(cnine::dims(d,d),cnine::fill::identity);
      apply_left(R,sigma);
      return R;
    }

    float character(const IntegerPartition& mu){
      rtensor R(cnine::dims(d,d),cnine::fill::identity);
      int a=1;
      for(int i=0; i<mu.k; i++){
	apply_left(R,ContiguousCycle(a,a+mu.p[i]-1));
	a+=mu.p[i];
      }
      float t=0;
      for(int i=0; i<d; i++){
	t+=R.get_value(i,i);
	//cout<<"t="<<t<<" "<<R.get_value(i,i)<<endl;
      }
      //cout<<" "<<t<<endl;
      return t;
    }



  public: // ---- Ancestors ---------------------------------------------------------------------------------




  public: // ---- apply_left to whole matrix ----------------------------------------------------------------


    void apply_left(rtensor& A, const SnElement sigma) const{
      SNOB2_ASSERT(sigma.getn()==n,"Permutation wrong size");
      vector<int> shifts(n);
      for(int i=n; i>0; i--){
	int a=sigma(i);
	shifts[i-1]=a;
	for(int j=1; j<i; j++) if(sigma.p[j-1]>a) sigma.p[j-1]--;
      }
      for(int i=2; i<=n; i++){
	//cout<<i<<" "<<shifts[i-1]<<endl;
	//cout<<A<<endl;
	for(int a=i-1; a>=shifts[i-1]; a--)
	  apply_left(A,a);
      }
    }

    void apply_left(rtensor& A, const ContiguousCycle& cyc) const{
      if(cyc.a<cyc.b){
	for(int i=cyc.b-1; i>=cyc.a; i--)
	  apply_left(A,i);
      }else{
	for(int i=cyc.b; i<cyc.a; i++)
	  apply_left(A,i);
      }
    }

    void apply_left_inv(rtensor& A, const ContiguousCycle& cyc) const{
      for(int i=cyc.a; i<cyc.b; i++)
	apply_left(A,i);
    }

    void apply_left(rtensor& A, const Transposition& x) const{
      int a=std::min(x.i,x.j);
      int b=std::max(x.i,x.j);
      for(int i=b-1; i>=a; i--)
	  apply_left(A,i);
      for(int i=a+1; i<b; i++)
	  apply_left(A,i);
    }

    void apply_left(rtensor& A, const int tau) const{
      SNOB2_ASSERT(A.get_dim(0)==d,"Matrix wrong size");
      const int J=A.get_dim(1);
      computeYOR();
      bool done[d];
      //cout<<"---"<<lambda<<endl<<endl;
      for(int i=0; i<d; i++) done[i]=false;
      for(int i=0; i<d; i++){
	if(done[i]) continue; 
	double c1,c2;
	const int i2=YOR(tau,i,c1,c2);
	if(i2==-1){
	  //cout<<"c1="<<c1<<endl;
	  for(int j=0; j<J; j++)
	    A.set_value(i,j,c1*A.get_value(i,j));
	}else{
	  //cout<<"c1="<<c1<<" c2="<<c2<<endl;
	  for(int j=0; j<J; j++){
	    float t=A.get_value(i,j);
	    A.set_value(i,j,c1*t+c2*A.get_value(i2,j));
	    A.set_value(i2,j,-c1*A.get_value(i2,j)+c2*t);
	  }
	  done[i2]=true;
	}
      }
    }


  public: // ---- apply to view ------------------------------------------------------------------------------
    // Each transformation is applied to the first index


    void apply_left(const cnine::Rtensor3_view& A, const SnElement sigma) const{
      SNOB2_ASSERT(sigma.getn()==n,"Permutation wrong size");
      vector<int> shifts(n);
      for(int i=n; i>0; i--){
	int a=sigma(i);
	shifts[i-1]=a;
	for(int j=1; j<i; j++) if(sigma.p[j-1]>a) sigma.p[j-1]--;
      }
      for(int i=2; i<=n; i++){
	for(int a=i-1; a>=shifts[i-1]; a--)
	  apply_left(A,a);
      }
    }


    void apply_left(const cnine::Rtensor3_view& A, const ContiguousCycle& cyc) const{
      if(cyc.a<cyc.b){
	for(int i=cyc.b-1; i>=cyc.a; i--)
	  apply_left(A,i);
      }else{
	for(int i=cyc.b; i<cyc.a; i++)
	  apply_left(A,i);
      }
    }


    void apply_left(const cnine::Rtensor3_view& A, const Transposition& x) const{
      int a=std::min(x.i,x.j);
      int b=std::max(x.i,x.j);
      for(int i=b-1; i>=a; i--)
	  apply_left(A,i);
      for(int i=a+1; i<b; i++)
	  apply_left(A,i);
    }


    void apply_left(const cnine::Rtensor3_view& T, const int tau) const{
      SNOB2_ASSERT(T.n0==d,"View wrong size");
      const int A=T.n1;
      const int B=T.n2;
      computeYORtensors();
      int ndiags=YORndiags->get(tau-1);
      cnine::ScaleSomeSlicesFn()(T,YORdiagIndices->view2().slice0(tau-1).block(0,ndiags),
	YORdiagCoeffs->view2().slice0(tau-1).block(0,ndiags));
      cnine::GivensSomeSlicesFn()(T,YORgivensIndices->view3().slice0(tau-1).block(0,0,(d-ndiags)/2,2),
	YORgivensCoeffs->view3().slice0(tau-1).block(0,0,(d-ndiags)/2,2));

      /*
      computeYOR();
      bool done[d];
      //cout<<"---"<<lambda<<endl<<endl;
      for(int i=0; i<d; i++) done[i]=false;
      for(int i=0; i<d; i++){
	if(done[i]) continue; 
	double c1,c2;
	const int i2=YOR(tau,i,c1,c2);
	if(i2==-1){
	  for(int a=0; a<A; a++)
	    for(int b=0; b<B; b++)
	      T.set(i,a,b,c1*T(i,a,b));
	}else{
	  for(int a=0; a<A; a++)
	    for(int b=0; b<B; b++){
	      float t=T(i,a,b);
	      T.set(i,a,b,c1*t+c2*T(i2,a,b));
	      T.set(i2,a,b,-c1*T(i2,a,b)+c2*t);
	    }
	  done[i2]=true;
	}
	}
      */
    }


  public: // ---- apply to view ------------------------------------------------------------------------------
    // Each transformation is applied to the middle index


    void apply(const cnine::Rtensor3_view& A, const SnElement sigma) const{
      SNOB2_ASSERT(sigma.getn()==n,"Permutation wrong size");
      vector<int> shifts(n);
      for(int i=n; i>0; i--){
	int a=sigma(i);
	shifts[i-1]=a;
	for(int j=1; j<i; j++) if(sigma.p[j-1]>a) sigma.p[j-1]--;
      }
      for(int i=2; i<=n; i++){
	for(int a=i-1; a>=shifts[i-1]; a--)
	  apply(A,a);
      }
    }


    void apply(const cnine::Rtensor3_view& A, const ContiguousCycle& cyc) const{
      if(cyc.a<cyc.b){
	for(int i=cyc.b-1; i>=cyc.a; i--)
	  apply(A,i);
      }else{
	for(int i=cyc.b; i<cyc.a; i++)
	  apply(A,i);
      }
    }


    void apply(const cnine::Rtensor3_view& A, const Transposition& x) const{
      int a=std::min(x.i,x.j);
      int b=std::max(x.i,x.j);
      for(int i=b-1; i>=a; i--)
	  apply(A,i);
      for(int i=a+1; i<b; i++)
	  apply(A,i);
    }


    void apply(const cnine::Rtensor3_view& T, const int tau) const{
      SNOB2_ASSERT(T.n1==d,"View wrong size");
      const int A=T.n0;
      const int B=T.n2;
      computeYOR();
      bool done[d];
      //cout<<"---"<<lambda<<endl<<endl;
      for(int i=0; i<d; i++) done[i]=false;
      for(int i=0; i<d; i++){
	if(done[i]) continue; 
	double c1,c2;
	const int i2=YOR(tau,i,c1,c2);
	if(i2==-1){
	  for(int a=0; a<A; a++)
	    for(int b=0; b<B; b++)
	      T.set(a,i,b,c1*T(a,i,b));
	}else{
	  for(int a=0; a<A; a++)
	    for(int b=0; b<B; b++){
	      float t=T(a,i,b);
	      T.set(a,i,b,c1*t+c2*T(a,i2,b));
	      T.set(a,i2,b,-c1*T(a,i2,b)+c2*t);
	    }
	  done[i2]=true;
	}
      }
    }


    void apply_transp(const cnine::Rtensor3_view& T, const int tau) const{
      apply(T,tau);
    }


  public: // ---- apply_left to block ------------------------------------------------------------------------


    void apply_left(rtensor& A, const SnElement sigma, int beg, int end) const{
      SNOB2_ASSERT(sigma.getn()==n,"Permutation wrong size");
      vector<int> shifts(n);
      for(int i=n; i>0; i--){
	int a=sigma(i);
	shifts[i-1]=a;
	for(int j=1; j<i; j++) if(sigma.p[j-1]>a) sigma.p[j-1]--;
      }
      for(int i=2; i<=n; i++){
	//cout<<i<<" "<<shifts[i-1]<<endl;
	//cout<<A<<endl;
	for(int a=i-1; a>=shifts[i-1]; a--)
	  apply_left(A,a,beg,end);
      }
    }

    void apply_left(rtensor& A, const ContiguousCycle& cyc, const int beg, const int end) const{
      for(int i=cyc.b-1; i>=cyc.a; i--)
	apply_left(A,i,beg,end);
    }

    void apply_left_inv(rtensor& A, const ContiguousCycle& cyc, const int beg, const int end) const{
      for(int i=cyc.a; i<cyc.b; i++)
	apply_left(A,i,beg,end);
    }

    void apply_left(rtensor& A, const int tau, int beg, int end) const{ // GPU
      SNOB2_ASSERT(A.get_dim(0)==d,"Matrix wrong size");
      //const int J=A.get_dim(1);
      computeYOR();
      bool done[d];
      for(int i=0; i<d; i++) done[i]=false;
      for(int i=0; i<d; i++){
	if(done[i]) continue; 
	double c1,c2;
	const int i2=YOR(tau,i,c1,c2);
	if(i2==-1){
	  for(int j=beg; j<end; j++)
	    A.set_value(i,j,c1*A.get_value(i,j));
	}else{
	  for(int j=beg; j<end; j++){
	    float t=A.get_value(i,j);
	    A.set_value(i,j,c1*t+c2*A.get_value(i2,j));
	    A.set_value(i2,j,-c1*A.get_value(i2,j)+c2*t);
	  }
	  done[i2]=true;
	}
      }
    }


  public: // ---- apply_left to multiple blocks --------------------------------------------------------------


    void apply_left(rtensor& A, const SnElement sigma, const int beg, const int end, const int stride) const{
      SNOB2_ASSERT(sigma.getn()==n,"Permutation wrong size");
      vector<int> shifts(n);
      for(int i=n; i>0; i--){
	int a=sigma(i);
	shifts[i-1]=a;
	for(int j=1; j<i; j++) if(sigma.p[j-1]>a) sigma.p[j-1]--;
      }
      for(int i=2; i<=n; i++){
	apply_left(A,ContiguousCycle(shifts[i-1],i),beg,end,stride);
      }
    }

    void apply_left(rtensor& A, const ContiguousCycle& cyc, const int beg, const int end, const int stride) const{
      for(int j=0; j<A.dim(1)/stride; j++)
	for(int i=cyc.b-1; i>=cyc.a; i--)
	  apply_left(A,i,beg+j*stride,end+j*stride);
    }


  private: // ---- YOR ---------------------------------------------------------------------------------------

    
    int YOR(const int tau, const int t, double& c1, double& c2) const {
      int index=t*(n-1)+tau-1; c1=YOR1[index]; c2=YOR2[index]; return YORt[index];
    }
  
    void computeYOR() const{
      if (YORt) return;
      //cout<<"Computing YOR for "<<lambda<<endl;
      YORt=new int[d*(n-1)];
      YOR1=new double[d*(n-1)];
      YOR2=new double[d*(n-1)];
      for(int i=0; i<d; i++){ // for each tableau...
	for(int tau=1; tau<n; tau++){ // for each transposition (tau,tau+1)...
	  const int ix=i*(n-1)+tau-1;
	  YoungTableau tableau(*tableaux[i]);
	  int delta=tableau.apply_transp(tau);
	  if((delta==1)||(delta==-1)){
	    YORt[ix]=-1; YOR1[ix]=delta; YOR2[ix]=0;
	  }else{
	    YORt[ix]=index(tableau);
	    //cout<<tableau.shape()<<" "<<i<<" "<<tau<<" "<<YORt[ix]<<" "<<delta<<endl;
	    YOR1[ix]=1.0/delta;
	    YOR2[ix]=sqrt(1.0-1.0/(delta*delta));
	  }
	}
      }

    }

    void computeYORtensors() const{
      if (YORndiags) return;
      YORndiags=new itensor(cnine::Gdims({n-1}),cnine::fill_zero());
      YORdiagIndices=new itensor(cnine::Gdims({n-1,d}),cnine::fill_zero());
      YORdiagCoeffs=new rtensor(cnine::Gdims({n-1,d}),cnine::fill_zero());
      YORgivensIndices=new itensor(cnine::Gdims({n-1,d/2+1,2}),cnine::fill_zero());
      YORgivensCoeffs=new rtensor(cnine::Gdims({n-1,d/2+1,2}),cnine::fill_zero());
      //cout<<"Computing YOR tensors for "<<lambda<<endl;
      for(int tau=1; tau<n; tau++){ // for each transposition (tau,tau+1)...
	int ix=0;
	vector<bool> done(d,false);
	for(int i=0; i<d; i++){ // for each tableau...
	  if(done[i]) continue;
	  YoungTableau tableau(*tableaux[i]);
	  int delta=tableau.apply_transp(tau);
	  if((delta==1)||(delta==-1)){
	    YORdiagIndices->set(tau-1,ix,i);
	    //cout<<YORdiagCoeffs->dev<<endl;
	    YORdiagCoeffs->set(tau-1,ix,delta);
	    ix++;
	  }else{
	    int j=index(tableau);
	    YORgivensIndices->set(tau-1,i-ix,0,i);
	    YORgivensIndices->set(tau-1,i-ix,1,j);
	    YORgivensCoeffs->set(tau-1,i-ix,0,1.0/delta);
	    YORgivensCoeffs->set(tau-1,i-ix,1,sqrt(1.0-1.0/(delta*delta)));
	    done[j]=true;
	  }
	}
	YORndiags->set(tau-1,ix);
      }

    }


  public: // ---- YJM ----------------------------------------------------------------------------------------


    const rtensor& JucysMurphy(const int k) const{
      assert(k<=n);
      if(YJM.exists(k)) return YJM[k];
      rtensor R(cnine::dims(d,d),cnine::fill::zero);
      rtensor A(cnine::dims(d,d),cnine::fill::identity);
      for(int i=k-1; i>=1; i--){
	apply_left(A,i);
	rtensor B(A);
	apply_left_inv(B,ContiguousCycle(i+1,k));
	R+=B;
      }
      YJM.insert(k,new rtensor(R.view2().diag()));
      return YJM[k];
    }


  public: // ---- I/O ----------------------------------------------------------------------------------------


    string str(const string indent="") const{
      return "SnIrrepObj("+lambda.str()+")";
    }

    friend ostream& operator<<(ostream& stream, const SnIrrepObj& x){
      stream<<x.str(); return stream;
    }

  };

}

#endif
    /*
    void apply_transposition(Rtensor2_view& T, const int tau) const{ // Applied to the first index 
      SNOB2_ASSERT(T.n0==d,"View wrong size");
      const int B=T.n1;
      computeYOR();
      bool done[d];
      //cout<<"---"<<lambda<<endl<<endl;
      for(int i=0; i<d; i++) done[i]=false;
      for(int i=0; i<d; i++){
	if(done[i]) continue; 
	double c1,c2;
	const int i2=YOR(tau,i,c1,c2);
	if(i2==-1){
	    for(int b=0; b<B; b++)
	      T.set(i,b,c1*T(i,b));
	}else{
	    for(int b=0; b<B; b++){
	      float t=T(i,b);
	      T.set(i,b,c1*t+c2*T(i2,b));
	      T.set(i2,b,-c1*T(i2,b)+c2*t);
	    }
	  done[i2]=true;
	}
      }
    }
    */

    /*
    void apply(Rtensor2_view& A, const ContiguousCycle& cyc) const{
      if(cyc.a<cyc.b){
	for(int i=cyc.b-1; i>=cyc.a; i--)
	  apply_left(A,i);
      }else{
	for(int i=cyc.b; i<cyc.a; i++)
	  apply_left(A,i);
      }
    }
    */

