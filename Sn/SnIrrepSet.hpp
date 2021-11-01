
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef _SnIrrepSet
#define _SnIrrepSet

#include "SnIrrepObj.hpp"

namespace Snob2{

  class SnIrrepSet{
  public:

    const SnIrrepObj* obj;
    IntegerPartition lambda;

  public:

    SnIrrep(const SnIrrepObj* _obj):
      obj(_obj), lambda(_obj->lambda){}

  };

}

#endif
