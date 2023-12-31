
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "CtensorObj.hpp"

#include "Group.hpp"
#include "CyclicGroupElement.hpp"

namespace Snob2 {

class CyclicGroupIrrep : public GroupIrrep {
public:
  int n;
  int k;

  typedef cnine::Gdims Gdims;
  typedef cnine::CtensorObj ctensor;

public:
  CyclicGroupIrrep(const int _n, const int _k) : n(_n), k(_k) {}

public:
  int dim() const { return 1; }

  ctensor operator()(const int i) const {
    ctensor r(Gdims({1}), cnine::fill_raw());
    float c = 2 * M_PI / n;
    r.set_value(0, complex<float>(cos(c * k * i), sin(c * k * i)));
    return r;
  }

  ctensor operator()(const CyclicGroupElement &x) const {
    ctensor r(Gdims({1}), cnine::fill_raw());
    float c = 2 * M_PI / n;
    r.set_value(0, complex<float>(cos(c * k * x.i), sin(c * k * x.i)));
    return r;
  }

public: // I/O
  string str(const string indent = "") const {
    return "CyclicGroupIrrep(" + to_string(n) + "," + to_string(k) + ")";
  }

  friend ostream &operator<<(ostream &stream, const CyclicGroupIrrep &x) {
    stream << x.str();
    return stream;
  }
};

} // namespace Snob2
