
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

#include "Sn_IrrepHelper.hpp"

using namespace cnine;
using namespace Snob2;


int main(int argc, char** argv){

  Snob2_session session;

  Sn G(5);

  cout<<G.irreps.size()<<endl<<endl;

  cout<<G.irreps[2]<<endl;
  cout<<G.irreps[IntegerPartition({4,1})]<<endl;
  cout<<endl;

  //for(auto it=G.irreps.begin(); it!=G.irreps.end(); it++)
  //cout<<*it<<endl;

  for(auto p:G.irreps) 
    cout<<p<<endl;

}
