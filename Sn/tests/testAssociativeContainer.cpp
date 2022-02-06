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

#include "associative_container.hpp"

using namespace cnine;
using namespace Snob2;

//typedef CscalarObj cscalar;
typedef RtensorObj rtensor;



int main(int argc, char** argv){

  Snob2_session session;

  associative_container<IntegerPartition,rtensor> A;

  A.insert(IntegerPartition({2}),rtensor::zero({2,2}));
  A.insert(IntegerPartition({1,1}),rtensor::ones({2,2}));
  
  cout<<A<<endl;

}
