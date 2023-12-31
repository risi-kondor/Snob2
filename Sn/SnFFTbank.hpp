
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _SnFFTbank
#define _SnFFTbank

#include "ClausenFFTObj.hpp"

namespace Snob2 {

class SnFFTbank {
public:
  unordered_map<ClausenFFTobjSignature, ClausenFFTObj *> ffts;

  ~SnFFTbank() {
    for (auto &p : ffts)
      delete p.second;
  }

public:
  ClausenFFTObj *get_FFT(const int n, const int m = -1) {
    ClausenFFTobjSignature s(n, m);
    auto it = ffts.find(s);
    if (it != ffts.end())
      return it->second;
    ClausenFFTObj *t;
    if (m > -1)
      t = new ClausenFFTObj(n, m);
    else
      t = new ClausenFFTObj(n);
    ffts[s] = t;
    return t;
  }
};

} // namespace Snob2

#endif
