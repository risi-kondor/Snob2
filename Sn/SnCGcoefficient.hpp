
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "SnCGbank.hpp"

namespace Snob2 {

class SnCGcoefficient {
public:
  int v;

  SnCGcoefficient(const IntegerPartition &mu1, const IntegerPartition &mu2,
                  const IntegerPartition &mu3) {
    v = _sncgbank->coeff(mu1, mu2, mu3);
  }

public:
  operator int() const { return v; }
};

} // namespace Snob2
