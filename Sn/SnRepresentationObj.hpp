
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef _SnRepresentationObj
#define _SnRepresentationObj

#include "SnIrrepObj.hpp"
#include "SnIsotypicObj.hpp"
#include "SnType.hpp"
#include "SnBank.hpp"


namespace Snob2{

  class SnRepresentationObj{
  public:

    map<IntegerPartition,SnIsotypicObj> isotypics;

    mutable SnRepresentationObj* induced=nullptr;
    mutable SnRepresentationObj* restricted=nullptr;


  public:

    SnRepresentationObj(){}

    SnRepresentationObj(const SnType& _type){
      for(auto p:_type._map){
	isotypics[p.first]=SnIsotypicObj(_snbank->get_irrep(p.first),p.second);
      }
    }

    
  public: // ---- Access -------------------------------------------------------------------------------------


    SnType get_type() const{
      SnType R;
      for(auto& p:isotypics)
	R._map[p.first]=p.second.m;
      return R;
    }

    SnRepresentationObj* get_induced(){
      if(!induced) make_induced();
      return induced;
    }

    SnRepresentationObj* get_restricted(){
      if(!restricted){cerr<<"No restricted repr"<<endl;exit(-1);}
      return restricted;
    }


  private:

    /*
    void add(const IntegerPartition& lambda, int m, const SnRepresentationObj* sub){
      if(isotypics.find(lambda)==isotypics.end()) 
	isotypics[lambda]=SnIsotypicObj(_snbank->get_irrep(lambda));
      SnIsotypicObj& iso=isotypics[lambda];
      iso.m+=m;
    }
    */

    void add(const IntegerPartition& lambda, SnIsotypicObj& sub){
      if(isotypics.find(lambda)==isotypics.end()) 
	isotypics[lambda]=SnIsotypicObj(_snbank->get_irrep(lambda));
      SnIsotypicObj& iso=isotypics[lambda];
      iso.m+=sub.m;
      iso.subs.push_back(&sub);
    }

    void make_induced(){
      SnType tau=get_type();
      induced=new SnRepresentationObj();
      SnRepresentationObj& mu=*induced;

      for(auto& p:isotypics){
	SnIsotypicObj& iso=p.second;
	IntegerPartition lambda=iso.irrep->lambda;
	int k=lambda.k;
	int m=iso.m;
	for(int i=0; i<k; i++)
	  if(i==0||lambda.p[i]<lambda.p[i-1]){
	    lambda.p[i]++;
	    //mu.add(lambda,m,this);
	    mu.add(lambda,iso);
	    lambda.p[i]--;
	  }
	lambda.add(k);
	//mu.add(lambda,m,this);
	mu.add(lambda,iso);
      }
      induced->restricted=const_cast<SnRepresentationObj*>(this);
    }


  public:

    string str(const string indent="") const{
      ostringstream oss;
      oss<<"SnRepresentationObj(";
      int i=0; 
      for(auto& p:isotypics){
	oss<<p.second;
	if(++i<isotypics.size()) oss<<",";
      }
      oss<<")"<<endl;
      return oss.str();
    }

    friend ostream& operator<<(ostream& stream, const SnRepresentationObj& x){
      stream<<x.str(); return stream;
    }


  };

}

#endif
