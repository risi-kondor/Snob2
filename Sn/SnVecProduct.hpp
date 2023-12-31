
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _SnVecProduct
#define _SnVecProduct

#include "SnVec.hpp"

namespace Snob2 {

class SnVecProduct {
public:
  SnVec &x;
  SnVec &y;

public
    : // ---- Constructors
      // -------------------------------------------------------------------------------
  SnVecProduct(const SnVec &_x, const SnVec &_y) : x(_x), y(_y){};

public
    : // ---- CG-product
      // ---------------------------------------------------------------------------------
  operator SnVec() const {}
};

} // namespace Snob2

#endif
