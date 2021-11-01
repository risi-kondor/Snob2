
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef _SnCharacter
#define _SnCharacter

#include "SnClassFunction.hpp"
#include "SnCharBank.hpp"
#include "SnCharacter.hpp"


namespace Snob2{

  class SnCharacter: public SnClassFunction{
  public:

    typedef cnine::RtensorObj rtensor;

    using SnClassFunction::get_value;


    IntegerPartition lambda;

    SnCharacter(const IntegerPartition& _lambda):
      SnClassFunction(*_sncharbank->get_character(_lambda)), lambda(_lambda){} // make it view



  public: // ---- Conversions -------------------------------------------------------------------------------


    SnCharacter(const SnClassFunction& x):
      SnClassFunction(x){}

    SnCharacter(SnClassFunction&& x):
      SnClassFunction(std::move(x)){}


  public: // ---- Access ------------------------------------------------------------------------------------


    //int size() const{
    //return dim(0);
    //}

    //float operator()(const IntegerPartition& lambda){
    // return rtensor::get_value(_snbank->get_Sn(lambda.getn())->index(lambda));
    //}

    //void set_value(const IntegerPartition& lambda, const float v){
    //rtensor::set_value(_snbank->get_Sn(lambda.getn())->index(lambda),v);
    //}
    


  public: // ---- I/O --------------------------------------------------------------------------------------- 


    string str(const string indent="") const{
      ostringstream oss;
      oss<<indent<<"chi"<<lambda<<":"<<endl;
      oss<<SnClassFunction::str(indent+"  ");
      return oss.str();
    }

    friend ostream& operator<<(ostream& stream, const SnCharacter& x){
      stream<<x.str(); return stream;
    }

  };

}

#endif
