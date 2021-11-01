
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#include "Snob2_base.cpp"
#include "Snob2_session.hpp"
#include "CombinatorialClasses.hpp"
#include "SnClasses.hpp"
#include "SnMultiVec.hpp"

using namespace cnine;
using namespace Snob2;

//typedef CscalarObj cscalar;
//typedef CtensorObj ctensor;



int main(int argc, char** argv){

  Snob2_session session;
  CombinatorialClasses combi_classes;
  SnClasses Snclasses;
  cout<<endl;

  Sn G(4);
  FunctionOnGroup<Sn,cnine::RtensorObj> f(G,cnine::fill::gaussian);
  cout<<f<<endl;

  SnMultiVec fv(f);
  printl("fv",fv);
}

