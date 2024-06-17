
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#include "GElib_base.cpp"
#include "GElibSession.hpp"

#include "RtensorObj.hpp"
#include "CtensorObj.hpp"
#include "GroupClasses.hpp"

using namespace cnine;
using namespace GElib;

//typedef CscalarObj cscalar;
//typedef RtensorObj rtensor;
//typedef CtensorObj ctensor;


int main(int argc, char** argv){
  GElibSession session;
  cout<<endl;

  CyclicGroup G(5);
  CyclicGroupElement g=G.element(2);
  FunctionOnGroup<CyclicGroup,rtensor> f(G,cnine::fill::gaussian);
  cout<<f<<endl;

  auto F=Fourier(f);
  cout<<F<<endl;

  auto fd=iFourier(F);
  cout<<fd<<endl;

  auto F2=F.left(g);
  auto f2d=iFourier(F2);
  cout<<f2d<<endl;

  auto F3=F.inv();
  auto f3d=iFourier(F3);
  cout<<f3d<<endl;

}

