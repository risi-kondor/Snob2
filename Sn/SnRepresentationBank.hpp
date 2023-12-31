
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include <map>

#include "SnRepresentationObj.hpp"

namespace Snob2 {

class SnRepresentationBank {
public:
  map<SnType, SnRepresentationObj *> reps;

  ~SnRepresentationBank() {
    for (auto p : reps)
      delete p.second;
  }

public:
  SnRepresentationObj *get_rep(const SnType &tau) {
    if (reps.find(tau) == reps.end())
      reps[tau] = new SnRepresentationObj(tau);
    return reps[tau];
  }
};

} // namespace Snob2
