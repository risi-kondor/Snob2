
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef _SnType
#define _SnType

#include "IntegerPartition.hpp"

namespace Snob2{

  class SnType: public map<IntegerPartition,int>{
  public:

    //mutable map<IntegerPartition,int> _map;
    

  public:

    SnType(){}

    SnType(const IntegerPartition& lambda, const int n){
      (*this)[lambda]=n;
      //_map[lambda]=n;
    }

    SnType(const initializer_list<tuple<IntegerPartition,int>> list){
      for(auto p: list) (*this)[std::get<0>(p)]=std::get<1>(p);
      //for(auto p: list) _map[std::get<0>(p)]=std::get<1>(p);
    }


  public: // ---- Access ------------------------------------------------------------------------------------


    int operator()(const IntegerPartition& lambda) const{
      return const_cast<SnType&>(*this)[lambda];//map<IntegerPartition,int>::operator[](lambda);
    }

    void set(const IntegerPartition& lambda, const int m){
      (*this)[lambda]=m;
      //_map[lambda]=m;
    }

    void add(const IntegerPartition& lambda, const int m){
      (*this)[lambda]+=m;
      //if(_map.find(lambda)==_map.end()) _map[lambda]=m;
      //else _map[lambda]=_map[lambda]+m;
    }

    map<IntegerPartition, int>& get_map(){
      return *this;
    }

  public:


    //bool operator==(const SnType& x) const{
    //return map<IntegerPartition,int>::operator==(x);
      //return _map==x._map;
    //}

    //bool operator<(const SnType& x) const{
    //return map<IntegerPartition,int>::operator<(x);
      //return _map<x._map;
    //}


  public:  // ---- Operations -------------------------------------------------------------------------------


    void add(const SnType& x, const int m=1){
      for(auto p:x)
	(*this)[p.first]+=m*p.second;
    }

    SnType static down(const SnType& tau){
      SnType R;
      for(auto& p:tau)
	p.first.foreach_sub([&](const IntegerPartition& mu){
	    R[mu]+=p.second;
	  });
      return R;
    }

    SnType static down(const IntegerPartition& lambda){
      SnType tau;
      lambda.foreach_sub([&](const IntegerPartition& mu){
	  tau[mu]++;
	  //tau._map[mu]++;
	});
      return tau;
    }

    SnType static cat(const vector<SnType*>& v){
      SnType tau;
      for(auto q:v)
	for(auto& p:*q)
	  tau.add(p.first,p.second);
      return tau;
   }


  public: // ---- I/O ---------------------------------------------------------------------------------------


    string str(const string indent="") const{
      ostringstream oss;
      int i=0; 
      oss<<"(";
      for(auto& p:*this){
	oss<<""<<p.first.str()<<":"<<p.second<<"";
	if(++i<size()) oss<<",";
      }
      oss<<")";
      return oss.str();
    }

    friend ostream& operator<<(ostream& stream, const SnType& x){
      stream<<x.str(); return stream;
    }


  };

}

#endif
