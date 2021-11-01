
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef _SnWeights
#define _SnWeights

#include "SnVec.hpp"
#include "RtensorObj_funs.hpp"


namespace Snob2{

  class SnWeights{
  public:

    typedef cnine::RtensorObj rtensor;

    unordered_map<IntegerPartition,rtensor*> weights;

    ~SnWeights(){
      for(auto p:weights)
	delete p.second;
    }


  public: // ---- Constructors -------------------------------------------------------------------------------


    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnWeights(const SnType& x, const SnType& y, const FILLTYPE& fill){
      for(auto& p: x._map){
	rtensor* mx=new rtensor(cnine::dims(p.second,y._map[p.first]),fill);
	weights[p.first]=mx;
      }
    }

    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnWeights(const SnVec& x, const SnVec& y, const FILLTYPE& fill){
      assert(x.parts.size()==y.parts.size());
      for(int i=0; i<x.parts.size(); i++){
	const SnPart& xp=*x.parts[i];
	const SnPart& yp=*y.parts[i];
	assert(xp.get_lambda()==yp.get_lambda());
	rtensor* mx=new rtensor(cnine::dims(xp.dims(1)*yp.dims(1)),fill);
	weights[xp.get_lambda()]=mx;
      }
    }

    
  public: // ---- Access -------------------------------------------------------------------------------------


    rtensor get_matrix(const IntegerPartition& lambda) const{
      auto it=weights.find(lambda);
      assert(it!=weights.end());
      return *it->second;
    }

    rtensor* get_matrixp(const IntegerPartition& lambda){
      auto it=weights.find(lambda);
      assert(it!=weights.end());
      return it->second;
    }


  public: // ---- Operations ---------------------------------------------------------------------------------

    SnVec operator*(const SnVec& y) const{
      SnVec R;
      for(auto p:y.parts){
	R.parts.push_back(new SnPart(p->irrep,(*p)*cnine::transp(get_matrix(p->get_lambda())))); 
      }
      return R;
    }


  public: // ---- I/O ----------------------------------------------------------------------------------------


    string str(string indent="") const{
      ostringstream oss;
      oss<<"SnWeights"<<endl;
      for(auto& p:weights){
	oss<<*p.second<<endl;
      }
      return oss.str();
    }

    friend ostream& operator<<(ostream& stream, const SnWeights& x){
      stream<<x.str(); return stream;
    }


  };

}

#endif
