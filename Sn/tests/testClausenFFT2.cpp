
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#include "Snob2_base.cpp"
#include "Snob2_session.hpp"
#include "SnOverSmFunction.hpp"
#include "ClausenFFT.hpp"

using namespace cnine;
using namespace Snob2;


int main(int argc, char** argv){
  Snob2_session session;

  int n=5;
  int m=3;


  ClausenFFT FFT(n,m);
  cout<<FFT<<endl;

  SnOverSmFunction f=SnOverSmFunction::gaussian(5,3);
  cout<<f<<endl;

  SnVec v=FFT(f);
  printl("v",v);

  auto fd=FFT.inv_snsm(v);
  printl("fd",fd);

}

