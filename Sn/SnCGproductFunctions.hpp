// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef _SnCGProductFunctions
#define _SnCGProductFunctions

#include "SnCGbank.hpp"

extern Snob2::SnCGbank* _sncgbank;


namespace Snob2{

  int CGcoefficient(const IntegerPartition& mu1, const IntegerPartition& mu2, const IntegerPartition& mu3){
    return _sncgbank->coeff(mu1,mu2,mu3);
  }

  SnType CGproduct(const IntegerPartition& mu1, const IntegerPartition& mu2){
    return SnType(_sncgbank->CGproduct(mu1,mu2));
  }


}

#endif
