
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
#include "RtensorObj.hpp"
#include "Gdims.hpp"
#include "SnOverSmFunction.hpp"

using namespace cnine;
using namespace Snob2;


int main(int argc, char** argv){
  Snob2_session session;

  Sn sn(4);
  SnOverSm X(4,3);
  SnOverSmFunction f(4,3,cnine::fill::gaussian);

  cout<<f<<endl;

  cout<<sn.element(3)<<endl;
  //cout<<f.left_translate(sn.element(3))<<endl;
  //cout<<f.right_translate(sn.element(3))<<endl;
}
