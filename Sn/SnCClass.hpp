
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "IntegerPartition.hpp"

namespace Snob2 {

class SnCClass : public IntegerPartition {
public:
  // IntegerPartition mu;

public:
  SnCClass(const IntegerPartition &_mu) : IntegerPartition(_mu) {}

public: // named constructors
        // static SnCClass Identity(const int n){
        // return Permutation(n,cnine::fill_identity());
        // }
public: // operations
  string str(const string indent = "") const {
    return indent + "SnCClass" + IntegerPartition::str();
  }

  friend ostream &operator<<(ostream &stream, const SnCClass &x) {
    stream << x.str();
    return stream;
  }
};

} // namespace Snob2
