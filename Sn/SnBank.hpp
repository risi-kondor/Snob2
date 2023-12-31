
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "Snob2_base.hpp"
#include "SnObj.hpp"
//#include "SnOverSmObj.hpp"
//#include "IntegerPartitionsObj.hpp"

namespace Snob2 {

class SnBank {
public:
  vector<SnObj *> sn;

  ~SnBank() {
    for (auto p : sn)
      delete p;
  }

public:
  SnObj *get_Sn(const int n) {
    if (n - 1 < sn.size())
      return sn[n - 1];
    const int _n = sn.size();
    sn.resize(n);
    for (int i = _n + 1; i <= n; i++) {
      sn[i - 1] = new SnObj(i);
      if (i > 1)
        sn[i - 1]->Snminus1 = sn[i - 2];
    }
    return sn[n - 1];
  }

  SnIrrepObj *get_irrep(const IntegerPartition &lambda) {
    return get_Sn(lambda.getn())->get_irrep(lambda);
  }

  SnOverSmObj *get_SnOverSm(const int n, const int m) {
    return get_Sn(n)->get_SnOverSm(m);
  }

public:
};

} // namespace Snob2
