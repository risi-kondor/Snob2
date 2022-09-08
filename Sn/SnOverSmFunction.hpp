
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef _SnOverSmFunction
#define _SnOverSmFunction

#include "SnOverSm.hpp"
#include "RtensorObj.hpp"


namespace Snob2{

  class SnOverSmFunction: public cnine::RtensorObj{ 
  public:

    typedef cnine::RtensorObj rtensor;

    const int n;
    const int m;
    //int N;
    //SnObj* G;

    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnOverSmFunction(int _n, int _m, const FILLTYPE& fill, const int _dev=0):
      rtensor({_snbank->get_SnOverSm(_n,_m)->order()},fill,_dev), n(_n), m(_m){
      //G=_snbank->get_Sn(n);
      //N=G->order;
    }

    SnOverSmFunction(const int _n, const int _m):
      SnOverSmFunction(_n,_m,cnine::fill_zero()){}



  public: // ---- Named constructors ------------------------------------------------------------------------


    SnOverSmFunction static raw(const int n, const int m, const int _dev=0){
      return SnOverSmFunction(n,m,cnine::fill_raw(),_dev);}

    SnOverSmFunction static zero(const int n, const int m, const int _dev=0){
      return SnOverSmFunction(n,m,cnine::fill_zero(),_dev);}

    SnOverSmFunction static ones(const int n, const int m, const int _dev=0){
      return SnOverSmFunction(n,m,cnine::fill_ones(),_dev);}

    SnOverSmFunction static gaussian(const int n, const int m, const int _dev=0){
      return SnOverSmFunction(n,m,cnine::fill_gaussian(),_dev);}

    SnOverSmFunction static sequential(const int n, const int m, const int _dev=0){
      return SnOverSmFunction(n,m,cnine::fill_sequential(),_dev);}


  public: // ---- Conversions --------------------------------------------------------------------------------


    SnOverSmFunction(const int _n, const int _m, const rtensor& M): 
      rtensor(M),
      n(_n),
      m(_m){}


  public: // ---- Access ------------------------------------------------------------------------------------


    int getN() const{
      return dims(0);
    }

    int size() const{
      return dims(0);
    }

    float get_value(const int i) const{
      return rtensor::value(i);
    }

    float get_value(const SnElement& x) const{
      const SnOverSmObj& G=*_snbank->get_SnOverSm(n,m);
      return rtensor::value(G.index(x));
    }

    SnOverSmFunction& set_value(const int i, const float v){
      rtensor::set_value(i,v);
      return *this;
    }

    SnOverSmFunction& set_value(const SnElement& x, const float v){
      int index = _snbank->get_SnOverSm(n,m)->index(x);
      rtensor::set_value(index,v);
      return *this;
    }


  public: // ---- I/O --------------------------------------------------------------------------------------- 


    string str(const string indent="") const{
      ostringstream oss;
      for(int i=0; i<dims(0); i++){
	      oss<<_snbank->get_SnOverSm(n,m)->element(i)<<" : ";
	      oss<<RtensorObj::get_value(i)<<endl;
      }
      return oss.str();
    }

    friend ostream& operator<<(ostream& stream, const SnOverSmFunction& x){
      stream<<x.str(); return stream;
    }


  };


}
    //:public FunctionOnGroup<SnOverSmObj,cnine::RtensorObj>{


#endif 
