
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
#include "SnRepresentation.hpp"

using namespace cnine;
using namespace Snob2;


int main(int argc, char** argv){

  Snob2_session session;
  //CombinatorialClasses combi_classes;
  //SnClasses Snclasses;

  SnType tau({{{4,2},1},{{3,3},4}});
  SnRepresentation mu(tau);
  cout<<mu<<endl;

  cout<<mu.induced()<<endl;




  Sn G(5);
  //cout<<G.repr()<<endl;

}
