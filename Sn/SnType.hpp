
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

  class SnType{
  public:

    mutable map<IntegerPartition,int> _map;
    

  public:

    SnType(){}

    SnType(const IntegerPartition& lambda, const int n){
      _map[lambda]=n;
    }

    SnType(const initializer_list<tuple<IntegerPartition,int>> list){
      for(auto p: list) _map[std::get<0>(p)]=std::get<1>(p);
    }


  public: // ---- Access ------------------------------------------------------------------------------------


    void set(const IntegerPartition& lambda, const int m){
      _map[lambda]=m;
    }

    void add(const IntegerPartition& lambda, const int m){
      if(_map.find(lambda)==_map.end()) _map[lambda]=m;
      else _map[lambda]=_map[lambda]+m;
    }


  public:


    bool operator==(const SnType& x) const{
      return _map==x._map;
    }

    bool operator<(const SnType& x) const{
      return _map<x._map;
    }


  public:  // ---- Operations -------------------------------------------------------------------------------


    SnType static down(const IntegerPartition& lambda){
      SnType tau;
      lambda.foreach_sub([&](const IntegerPartition& mu){
	  tau._map[mu]++;
	});
      return tau;
    }

    SnType static cat(const vector<SnType*>& v){
      SnType tau;
      for(auto q:v)
	for(auto& p:q->_map)
	  tau.add(p.first,p.second);
      return tau;
   }


  public: // ---- I/O ---------------------------------------------------------------------------------------


    string str(const string indent="") const{
      ostringstream oss;
      int i=0; 
      oss<<"(";
      for(auto& p:_map){
	oss<<""<<p.first.str()<<":"<<p.second<<"";
	if(++i<_map.size()) oss<<",";
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
