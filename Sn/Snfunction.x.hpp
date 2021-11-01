
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#include "Sn.hpp"
#include "FunctionOnGroup.hpp"
#include "RtensorObj.hpp"


namespace Snob2{

  class SnFunction: public FunctionOnGroup<SnObj,cnine::RtensorObj>{
  public:

    using FunctionOnGroup::FunctionOnGroup;

    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnFunction(int n, const FILLTYPE& fill, const int _dev=0):
      FunctionOnGroup<SnObj,cnine::RtensorObj>(_snbank->get_Sn(n),fill,_dev){}

    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnFunction(const Sn& _G, const FILLTYPE& fill, const int _dev=0):
      FunctionOnGroup<SnObj,cnine::RtensorObj>(_G.obj,fill,_dev){}


  public: // ---- Named constructors ------------------------------------------------------------------------


    SnFunction static raw(const int n, const int _dev=0){
      return SnFunction(n,cnine::fill_raw(),_dev);}

    SnFunction static zero(const int n, const int _dev=0){
      return SnFunction(n,cnine::fill_zero(),_dev);}

    SnFunction static gaussian(const int n, const int _dev=0){
      return SnFunction(n,cnine::fill_gaussian(),_dev);}


  public: // ---- I/O --------------------------------------------------------------------------------------- 


    string str(const string indent="") const{
      ostringstream oss;
      for(int i=0; i<N; i++){
	//oss<<G.element(i)<<" : ";  // Fix this!
	oss<<RtensorObj::get_value(i)<<endl;
      }
      return oss.str();
    }

    friend ostream& operator<<(ostream& stream, const SnFunction& x){
      stream<<x.str(); return stream;
    }


  };


}
