
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


using namespace cnine;
using namespace Snob2;

//typedef CscalarObj cscalar;
//typedef CtensorObj ctensor;



int main(int argc, char** argv){

  Snob2_session session;

  Sn G(4);
  cout<<G.get_order()<<endl;

  SnElement sigma=G.identity(); 
  cout<<sigma<<endl;
  cout<<endl; 

  for(auto p:G.elements)
    cout<<p<<endl;
  cout<<endl;

  for(auto p:G.cclasses)
    cout<<p<<endl;
  cout<<endl;

  for(auto p:G.irreps)
    cout<<p<<endl;
  cout<<endl;

  for(auto p:G.characters)
    cout<<p<<endl;
  cout<<endl;


  //SnModule M=G.module();
  //cout<<M<<endl;

}


  //auto irreps=G.all_irreps();
  //for(auto p:irreps) cout<<p<<" "<<p.dim()<<endl;

