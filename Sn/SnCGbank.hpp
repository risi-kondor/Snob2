
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef _SnCGbank
#define _SnCGbank

#include "SnWeights.hpp"
#include "SnCharacter.hpp"
#include "associative_container.hpp"
#include "SnVecB.hpp"
#include "SnProductRepresentation.hpp"

#include "SymmetricEigendecomp.hpp"


namespace Snob2{

  //typedef cnine::RtensorObj rtensor;

  class SnCGfactors: 
    public cnine::associative_container<IntegerPartition,rtensor>{

    //public associative_container<IntegerPartition,associative_container<IntegerPartition,rtensor> >{
    
    //using associative_container<IntegerPartition,associative_container<IntegerPartition,rtensor> >::
    //associative_container<IntegerPartition,associative_container<IntegerPartition,rtensor> >;

  };


  class SnCGbank{
  public:

    unordered_map<tuple<IntegerPartition,IntegerPartition,IntegerPartition>,int> coeffs;
    unordered_map<pair<IntegerPartition,IntegerPartition>,SnType*> taus;
    //unordered_map<pair<IntegerPartition,IntegerPartition>,SnWeights*> tables;
    unordered_map<pair<IntegerPartition,IntegerPartition>,SnCGfactors*> factors;

    ~SnCGbank(){
      for(auto& p:taus)
	delete p.second;
      //for(auto& p:tables)
      //delete p.second;
      for(auto& p:factors)
	delete p.second;
      }
    

  public:

    int coeff(const IntegerPartition& _mu1, const IntegerPartition& _mu2, const IntegerPartition& _mu3){
      auto mus=order(_mu1,_mu2,_mu3);
      auto it=coeffs.find(mus);
      if(it!=coeffs.end()) return it->second;
      
      const int n=_mu1.getn();
      assert(_mu1.getn()==_mu2.getn());
      assert(_mu1.getn()==_mu3.getn());

      Sn G(n);
      SnCharacter ch1(_mu1);
      SnCharacter ch2(_mu2);
      SnCharacter ch3(_mu3);
      int N=ch1.size();

      float t=0;
      for(int i=0; i<N; i++){
	t+=ch1(i)*ch2(i)*ch3(i)*G.class_size(i);
      }
      t/=G.size();
      coeffs[mus]=t;
      return t;
    }


    const SnType& CGproduct(const IntegerPartition& lambda1, const IntegerPartition& lambda2){
      pair<IntegerPartition,IntegerPartition> lambdas(lambda1,lambda2);
      auto it=taus.find(lambdas);
      if(it!=taus.end()) return *it->second;

      int n=lambda1.getn();
      int limit=2*n-lambda1[0]-lambda2[0];
      SnType* tau=new SnType();
      IntegerPartitions all_lambdas(n);
      for(auto p:*all_lambdas.lambda)
	if((*p)[0]>=n-limit){
	  int m=coeff(lambda1,lambda2,*p);
	  if(m>0) tau->add(*p,m);
	}    
      taus[lambdas]=tau;
      return *tau;
    }


    SnType CGproduct(const SnType& tau1, const SnType& tau2){
      SnType R;
      for(auto& p:tau1)
	for(auto& q:tau2)
	  R.add(CGproduct(p.first,q.first),p.second*q.second);
      return R;
    }


    const SnCGfactors& get_CGfactors(const IntegerPartition& lambda1, const IntegerPartition& lambda2){
      pair<IntegerPartition,IntegerPartition> lambdas(lambda1,lambda2);
      auto it=factors.find(lambdas);
      if(it!=factors.end()) return *it->second;

      SnCGfactors* R=new SnCGfactors();
      SnType sub=SnType::down(CGproduct(lambda1,lambda2));
      for(auto& p:sub){
	R->insert(p.first,rtensor::identity({p.second,p.second}));
      }
      learn(*R, lambda1,lambda2);
      factors[lambdas]=R;
      CheckCG(lambda1,lambda2);
      return *R;
    }
    

    void learn(SnCGfactors& R, const IntegerPartition& lamb1, const IntegerPartition& lamb2){
      cout<<"---- Learning transformation for "<<lamb1<<" * "<<lamb2<<" -> "<<CGproduct(lamb1,lamb2)<<endl;

      SnIrrep rho1(lamb1);
      SnIrrep rho2(lamb2);
      int d1=rho1.getd();
      int d2=rho2.getd();
      int d=d1*d2;
      int n=rho1.getn();

      SnProductRepresentation<SnIrrep,SnIrrep> rho(rho1,rho2);
      rtensor JM=rho.JucysMurphy(n);
      printl("JM",JM);
      cnine::SymmetricEigendecomp eig(JM.view2());
      cout<<"evals: "<<eig.D<<endl;
      for(auto p: CGproduct(lamb1,lamb2)){
	cout<<"JM for "<<p.first<<":"<<endl;
	cout<<SnIrrep(p.first).JucysMurphy(p.first.getn())<<endl;
      }

      SnPartB p1=SnPartB::zero(d,lamb1,1);
      for(int i=0; i<d1; i++)
	for(int j=0; j<d2; j++)
	  //for(int k=0; k<d1; k++)
	    p1(i*d2+j,i,0)=1;

      SnPartB p2=SnPartB::zero(d,lamb2,1);
      for(int i=0; i<d1; i++)
	for(int j=0; j<d2; j++)
	  //for(int k=0; k<d2; k++)
	    p2(i*d2+j,j,0)=1;
      
      SnVecB xsub=SnVecB::down(p1);
      SnVecB ysub=SnVecB::down(p2);
      SnVecB sub=CGproduct(xsub,ysub);
      cout<<sub.get_type()<<endl;

      cnine::associative_container<IntegerPartition,rtensor> evectors;
      cnine::associative_container<IntegerPartition,rtensor> evalues;
      for(auto p: sub){
	cnine::Rtensor2_view V=p.view3().slice1(0);
	rtensor M=V.transp()*(JM.view2())*V;
	cnine::SymmetricEigendecomp eig(M.view2());
	cout<<"Part "<<p.get_lambda()<<" "<<endl;
	printl("V",V);
	printl("M",M);
	printl("U",eig.U);
	printl("D",eig.D);
	//cout<<p.get_rho().JucysMurphy(n-1)<<endl;
	//cout<<p.get_rho().JucysMurphy(n-1)<<endl;
	evectors.insert(p.get_lambda(),eig.U);
	evalues.insert(p.get_lambda(),eig.D);
      }

      SnType tau=CGproduct(lamb1,lamb2);
      SnType taken;
      for(auto p:tau){
	cout<<"  "<<"Pulling to "<<p.first<<" with multiplicity "<<p.second<<endl;
	rtensor JMlamb=SnIrrep(p.first).JucysMurphy(p.first.getn());
	printl("JMlamb",JMlamb);
	int dlamb=SnIrrep(p.first).getd();
	//associative_container<IntegerPartition,rtensor> retractor;
	rtensor pullback;

	int offs=0;
	bool first_mu=true;
	p.first.foreach_sub([&](const IntegerPartition& mu){
	    cout<<"    Source "<<mu<<endl;
	    float target_eval=JMlamb.get_value(offs);
	    SnPartB& _sub=sub[mu];
	    rtensor& evals=evalues[mu];
	    //cout<<evals<<endl;
	    int dmu=_sub.getm();
	    //cout<<"dmu="<<dmu<<endl;
	    for(int k=0; k<p.second; k++){
	      cout<<"Looking for eigenvalue "<<target_eval<<endl;
	      int i=0; while(i<dmu && abs(evals.get_value(i)-target_eval)>0.001){i++;}
	      if(i==dmu){cout<<"Panic: eigenvalue not found!"<<endl; exit(-1);}
	      cout<<"Found."<<endl;
	      R[mu].view2().slice1(taken[mu]).set(evectors[mu].view2().slice1(i));
	      evals.set(i,1234567);
	      taken[mu]++;
	    }

	    if(first_mu){
	      pullback=(sub[mu].view3().slice1(0))*(R[mu].block2(0,taken[mu]-p.second,-1,p.second));
	      rho.apply(split0(pullback.view2(),1,d),n-1);
	      first_mu=false;
	    }else{
	      rtensor M=(sub[mu].view3().slice1(0).transp())*(pullback.view2());
	      rtensor B=(R[mu].block2(0,taken[mu]-p.second,-1,p.second).transp())*M;
	      cout<<"-----> "<<B<<endl;
	      rtensor A=rtensor::zero({1,dlamb,p.second});
	      for(int i=0; i<p.second; i++) A.set(0,0,i,1);
	      SnIrrep(p.first).apply(A.view3(),n-1);
	      cout<<"======> "<<A.view3().slice0(0).slice0(offs)<<endl;
	      //cout<<R[mu].block2(0,taken[mu]-p.second,-1,p.second)<<endl<<endl;
	      //cout<<(B.view2().transp()*(1.0/A.get_value(0,offs,0))).view2()<<endl;
	      if(abs(A.get_value(0,offs,0))>0.0001){
		rtensor C=R[mu].block2(0,taken[mu]-p.second,-1,p.second)*(B.view2().transp()*(1.0/A.get_value(0,offs,0)));
		R[mu].block2(0,taken[mu]-p.second,-1,p.second).set(C.view2());
	      }
	    }

	    offs+=_sub.getd();
	  });
      }

      cout<<"---- end learning"<<endl;
    }


    SnVec CGproduct(const SnVec& x, const SnVec& y, const string indent=""){
      SnVec R=SnVec::zero(CGproduct(x.get_type(),y.get_type()));
      //cout<<indent<<x.get_type()<<"*"<<y.get_type()<<"="<<CGproduct(x.get_type(),y.get_type())<<endl;
      add_CGprod(R,x,y,indent);
      return R;
    }


    SnVec CGproduct(const SnPart& x, const SnPart& y){
      SnVec R=SnVec::zero(CGproduct(x.get_lambda(),y.get_lambda()));
      SnType offs;
      accumulate_CGprod(R,offs,x,y);
      return R;
    }


    void add_CGprod(SnVec& R, const SnVec& x, const SnVec& y, const string indent=""){
      SNOB2_CGBANK_DEBUG(cout<<indent<<"Multiply("<<x.get_type()<<","<<y.get_type()<<") into "<<R.get_type()<<endl;)
      SnType offs;
      for(auto p:x.parts)
	for(auto q:y.parts){
	  accumulate_CGprod(R,offs,*p,*q,indent+"  ");
	}
      SNOB2_CGBANK_DEBUG(cout<<indent<<"."<<endl;)
    }


    void accumulate_CGprod(SnVec& R, SnType& offs, const SnPart& x, const SnPart& y, const string indent=""){
      SNOB2_CGBANK_DEBUG(cout<<indent<<"Accumulate("<<x.get_lambda()<<","<<y.get_lambda()<<") into "<<R.get_type()<<" with offset "<<offs<<endl;)
      const int n=x.getn();
      assert(y.getn()==n);

      if(n==1){
	int I=x.getm();
	int J=y.getm();
	for(int i=0; i<I; i++)
	  for(int j=0; j<J; j++)
	    R.parts[0]->inc(0,i*J+j,x(0,i)*y(0,j));
	offs[IntegerPartition({1})]+=I*J;
	SNOB2_CGBANK_DEBUG(cout<<indent<<"."<<endl;)
	return;
      }
    
      SnVec xsub=SnVec::downB(x);
      SnVec ysub=SnVec::downB(y);
      SnVec sub=CGproduct(xsub,ysub,indent+"  ");

      SnVec sub_tilde;
      for(auto p: get_CGfactors(x.get_lambda(),y.get_lambda()).keyval()){
	IntegerPartition mu=p.key();
	assert(sub.parts.exists(mu));
	sub_tilde.parts.insert(mu, new SnPart(SnIrrep(mu),(*sub.parts[mu])*(*p)));
      }
      
      R.accumulate_up(offs,sub_tilde,CGproduct(x.get_lambda(),y.get_lambda()),indent+"  ");
      SNOB2_CGBANK_DEBUG(cout<<indent<<"."<<endl;)
    }


    void CheckCG(const IntegerPartition& lamb1, const IntegerPartition& lamb2){
      cout<<endl<<"---- Checking "<<lamb1<<" * "<<lamb2<<endl<<endl;
      int n=lamb1.getn();
      SnPartB x=SnPartB::gaussian(1,lamb1,1);
      SnPartB y=SnPartB::gaussian(1,lamb2,1);
      
      for(int i=1; i<n; i++){
	cout<<">>>>>>>>"<<Transposition(i)<<endl;
	//cout<<x<<y<<x.apply(Transposition(i))<<y.apply(Transposition(i))<<endl<<endl;
	//cout<<CGproduct(x,y)<<endl;
	cout<<CGproduct(x.apply(Transposition(i)),y.apply(Transposition(i)));
	cout<<CGproduct(x,y).apply(Transposition(i))<<endl;
      }

    }

 

  public: // ---- SnVecB functions ---------------------------------------------------------------------------


    SnVecB CGproduct(const SnVecB& x, const SnVecB& y, const string indent=""){
      SnVecB R=SnVecB::zero(sameb(x,y),CGproduct(x.get_type(),y.get_type()));
      add_CGprod(R,x,y,indent);
      return R;
    }


    SnVecB CGproduct(const SnPartB& x, const SnPartB& y){
      SnVecB R=SnVecB::zero(sameb(x,y),CGproduct(x.get_lambda(),y.get_lambda()));
      SnType offs;
      accumulate_CGprod(R,offs,x,y);
      return R;
    }


    void add_CGprod(SnVecB& R, const SnVecB& x, const SnVecB& y, const string indent=""){
      SNOB2_CGBANK_DEBUG(cout<<indent<<"Multiply("<<x.get_type()<<","<<y.get_type()<<") into "<<R.get_type()<<endl;)
      SnType offs;
      for(auto p:x)
	for(auto q:y){
	  accumulate_CGprod(R,offs,p,q,indent+"  ");
	}
      SNOB2_CGBANK_DEBUG(cout<<indent<<"."<<endl;)
    }


    void accumulate_CGprod(SnVecB& R, SnType& offs, const SnPartB& x, const SnPartB& y, const string indent=""){
      SNOB2_CGBANK_DEBUG(cout<<indent<<"Accumulate("<<x.get_lambda()<<","<<y.get_lambda()<<") into "<<R.get_type()<<" with offset "<<offs<<endl;)
      const int nb=sameb(R,x,y);
      const int n=x.getn();
      assert(y.getn()==n);

      if(n==1){
	int I=x.getm();
	int J=y.getm();
	for(int b=0; b<nb; b++){
	  for(int i=0; i<I; i++)
	    for(int j=0; j<J; j++)
	      R.first().inc(b,0,i*J+j,x(b,0,i)*y(b,0,j));
	}
	offs[IntegerPartition({1})]+=I*J;
	SNOB2_CGBANK_DEBUG(cout<<indent<<"."<<endl;)
	return;
      }
    
      SnVecB xsub=SnVecB::down(x);
      SnVecB ysub=SnVecB::down(y);
      SnVecB sub=CGproduct(xsub,ysub,indent+"  ");

      SnVecB sub_tilde;
      for(auto p: get_CGfactors(x.get_lambda(),y.get_lambda()).keyval()){
	IntegerPartition mu=p.key();
	assert(sub.exists(mu));
	sub_tilde.insert(mu, new SnPartB(SnIrrep(mu),sub[mu]*(*p)));
      }

      R.accumulate_up(offs,sub_tilde,CGproduct(x.get_lambda(),y.get_lambda()),indent+"  ");
      SNOB2_CGBANK_DEBUG(cout<<indent<<"."<<endl;)
    }


  };


}

#endif
    /*
    SnWeights* getW(const IntegerPartition& lambda1, const IntegerPartition& lambda2){
      pair<IntegerPartition,IntegerPartition> lambdas(lambda1,lambda2);
      auto it=tables.find(lambdas);
      if(it!=tables.end()) return it->second;

      SnType xsub=SnType::down(lambda1);
      SnType ysub=SnType::down(lambda2);

      vector<SnType*> subs;
      for(auto p:xsub._map)
	for(auto q:ysub._map){
	  //cout<<"<"<<p->irrep->lambda<<","<<q->irrep->lambda<<">"<<endl;
	  subs.push_back(get_type(p.first,q.first));
	}
      SnType sub=SnType::cat(subs);

      //SnType* tau=get_type(lambda1,lambda2);
      SnWeights* table=new SnWeights(sub,sub,cnine::fill::identity); // TODO 
      tables[lambdas]=table;

      auto M=sequester(lambda1,lambda2);
      return table;
      return new SnWeights();
    }
    */

    /*
    rtensor sequester(const IntegerPartition& lambda1, const IntegerPartition& lambda2){
      SnType* tau=get_type(lambda1,lambda2);
      for(auto& p:*tau){
	if(p.second>1){cerr<<"Error: output multiplicity >1"<<endl;}
      }

      return rtensor(cnine::dims(1,1),cnine::fill::zero);

    }
    */


    //SnType* CGproductp(const IntegerPartition& lambda1, const IntegerPartition& lambda2){
    //return get_type(lambda1,lambda2);
    //}


    //SnType get_type(const IntegerPartition& lambda1, const IntegerPartition& lambda2){
    //return SnType(*get_typep(lambda1,lambda2));
    //}
    
      /*
      for(auto& p:sub){
	typedef associative_container<IntegerPartition,rtensor> subfact;
	subfact* sub=new subfact();
	p.first.foreach_sub([&](const IntegerPartition& mu){
	    int d=p.second;
	    sub->insert(mu,rtensor::identity({d,d}));
	  });
	R->insert(p.first,sub);
      }
      */
   /*
    SnVec CGprod(const SnPart& x, const SnPart& y){
      int n=x.getn();
      if(n==1){
	return SnVec(new SnPart(_snbank->get_irrep({1}),x(0,0)*y(0,0)));
      }

      SnVec xsub=SnVec::down(x);
      SnVec ysub=SnVec::down(y);

      //SnVec sub=SnVec::zeros()

      vector<SnVec> subs;
      for(auto p:xsub.parts)
	for(auto q:ysub.parts){
	  //cout<<"<"<<p->irrep->lambda<<","<<q->irrep->lambda<<">"<<endl;
	  subs.push_back(SnVec(CGprod(*p,*q)));
	}
      SnVec sub=SnVec::cat(subs);
      //cout<<sub<<endl<<"----"<<endl;
      SnType* tau=get_type(x.get_lambda(),y.get_lambda());
      SnWeights* W=getW(x.get_lambda(),y.get_lambda());
      return SnVec::up(*tau,(*W)*sub);
      return SnVec();
    }
    */
      /*
      auto Lambda1=StandardYoungTableaux(lambda1);
      auto Lambda2=StandardYoungTableaux(lambda2);

      for(int i1=0; i1<Lambda1.size(); i1++){
	auto t1=Lambda1[i1];
	int sign=(t1.nrows()>1 && t1(1,0)==2);
	SnPart p1=SnPart::zero(lambda1,1);
	p1.set(i1,0,1);

	for(int i2=0; i2<Lambda2.size(); i2++){
	  auto t2=Lambda2[i2];
	  if(t2.nrows()>1 && t2(1,0)==2) sign=1-sign;
	  if(sign==1) continue;
	  SnPart p2=SnPart::zero(lambda2,1);
	  p2.set(i2,0,1);

	  SnVec xsub=SnVec::downB(p1);
	  SnVec ysub=SnVec::downB(p2);
	  SnVec sub=CGproduct(xsub,ysub);

	  
	}
      }
      */
