
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
#include "SnPart.hpp"


using namespace cnine;
using namespace Snob2;


int main(int argc, char** argv){

  Snob2_session session;

  int n=4;
  Sn G(n);
  IntegerPartition lambda({n-1,1});
  SnIrrep rho(lambda); 
  SnElement sigma({1,2,4,3}); 

  SnPart A=SnPart::identity(rho,3);
  cout<<A<<endl;

  SnPart B=SnPart::identity(lambda,3);
  cout<<B<<endl;

  SnPart C=B.apply(sigma);
  printl("C",C);

}
