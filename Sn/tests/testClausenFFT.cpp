
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#include "Snob2_base.cpp"
#include "Snob2_session.hpp"
#include "SnClasses.hpp"
#include "FunctionOnGroup.hpp"
//#include "RtensorObj.hpp"
//#include "Gdims.hpp"
#include "SnVec.hpp" 
#include "CombinatorialClasses.hpp"
//#include "ClausenFFTObj.hpp"
#include "ClausenFFT.hpp"
#include "SnFunction.hpp"

using namespace cnine;
using namespace Snob2;

//typedef CscalarObj cscalar;
//typedef CtensorObj ctensor;



int main(int argc, char** argv){
  Snob2_session session;

  int n=4;

  ClausenFFT FFT(n); 

  SnFunction f(n,cnine::fill::gaussian);
  cout<<f<<endl;

  //cout<<FFT(f)<<endl;
  SnVec v=FFT(f);
  printl("v",v);

  auto fd=FFT.inv(v);
  printl("fd",fd);

}

