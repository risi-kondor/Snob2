
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


namespace Snob2{

  typedef cnine::RtensorObj rtensor;

  class SnCGfactors: 
    public associative_container<IntegerPartition,associative_container<IntegerPartition,rtensor> >{
    
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


    SnType* get_type(const IntegerPartition& lambda1, const IntegerPartition& lambda2){
      pair<IntegerPartition,IntegerPartition> lambdas(lambda1,lambda2);
      auto it=taus.find(lambdas);
      if(it!=taus.end()) return it->second;

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
      return tau;
    }


    SnType* CGproductp(const IntegerPartition& lambda1, const IntegerPartition& lambda2){
      return get_type(lambda1,lambda2);
    }


    SnType CGproduct(const SnType& tau1, const SnType& tau2){
      SnType R;
      for(auto& p:tau1)
	for(auto& q:tau1){
	  SnType* x=CGproductp(p.first,q.first);
	  //R._map*CGproductp(p
	}
      return R;
    }

    //SnType get_type(const IntegerPartition& lambda1, const IntegerPartition& lambda2){
    //return SnType(*get_typep(lambda1,lambda2));
    //}
    
    SnCGfactors* get_CGfactors(const IntegerPartition& lambda1, const IntegerPartition& lambda2){
      pair<IntegerPartition,IntegerPartition> lambdas(lambda1,lambda2);
      auto it=factors.find(lambdas);
      if(it!=factors.end()) return it->second;
      
      SnCGfactors* R=new SnCGfactors();

      factors[lambdas]=R;
      SnType* prod=get_type(lambda1,lambda2);
      for(auto& p:*prod){
	typedef associative_container<IntegerPartition,rtensor> subfact;
	subfact* sub=new subfact();
	p.first.foreach_sub([&](const IntegerPartition& mu){
	    int d=p.second;
	    sub->insert(mu,rtensor::identity({d,d}));
	  });
	R->insert(p.first,sub);
      }
      return R;
    }
    


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

    rtensor sequester(const IntegerPartition& lambda1, const IntegerPartition& lambda2){
      SnType* tau=get_type(lambda1,lambda2);
      for(auto& p:*tau){
	if(p.second>1){cerr<<"Error: output multiplicity >1"<<endl;}

	

      }

      return rtensor(cnine::dims(1,1),cnine::fill::zero);

    }


    SnVec CGprod(const SnPart& x, const SnPart& y){
      int n=x.getn();
      if(n==1){
	return SnVec(new SnPart(_snbank->get_irrep({1}),x(0,0)*y(0,0)));
      }

      SnVec xsub=SnVec::down(x);
      SnVec ysub=SnVec::down(y);

      //SnVec sub=SnVec::zeros()

      /*
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
      */
      return SnVec();
    }


  public:


  };


}

#endif
