
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include <map>

#include "IntegerPartition.hpp"
#include "SnIrrep.hpp"

namespace Snob2 {

class SnRepresentation {
public:
  // map<IntegerPartition,int> map;
  map<SnIrrep, int> irreps;

public:
  SnRepresentation() {}

  SnRepresentation(const SnIrrep &rho, const int n) { irreps[rho] = n; }

  SnRepresentation(const IntegerPartition &lambda, const int n) {
    irreps[SnIrrep(lambda)] = n; //_snbank->get_irrep(lambda);
  }

public:
  void set(const SnIrrep &rho, const int n) { irreps[rho] = n; }

public:
  string str(const string indent = "") const {
    ostringstream oss;
    oss << "SnRepresentation(";
    int i = 0;
    for (auto &p : irreps) {
      oss << "(" << p.first.lambda.str() << ":" << p.second << ")";
      if (++i < irreps.size())
        oss << ",";
    }
    oss << ")" << endl;
    return oss.str();
  }

  friend ostream &operator<<(ostream &stream, const SnRepresentation &x) {
    stream << x.str();
    return stream;
  }
};

} // namespace Snob2
