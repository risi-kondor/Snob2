
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "SnIrrepObj.hpp"

namespace Snob2 {

class SnIsotypicObj {
public:
  const SnIrrepObj *irrep;
  vector<SnIsotypicObj *> subs;
  int m;

public:
  SnIsotypicObj() {}

  SnIsotypicObj(const SnIrrepObj *_irrep, int _m = 0) : irrep(_irrep), m(_m) {}

public:
  string str(const string indent = "") const {
    ostringstream oss;
    oss << "" << irrep->lambda << ":" << m << "";
    return oss.str();
  }

  friend ostream &operator<<(ostream &stream, const SnIsotypicObj &x) {
    stream << x.str();
    return stream;
  }
};

} // namespace Snob2
