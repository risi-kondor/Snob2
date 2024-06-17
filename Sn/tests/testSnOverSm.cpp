
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


using namespace cnine;
using namespace Snob2;


int main(int argc, char** argv){
  Snob2_session session;

  SnOverSm Q(5,3);
  cout<<Q.get_order()<<endl;

  SnElement sigma=Q.identity(); 
  cout<<sigma<<endl;
  cout<<endl; 

  int N=Q.get_order();
  for(int i=0; i<N; i++){
    //cout<<sn.element(i)<<endl;
    cout<<Q.element(i)<<" "<<Q.index(Q.element(i))<<endl;
  }

}
