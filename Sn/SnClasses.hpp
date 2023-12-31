
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "Snob2_base.hpp"
#include "SnBank.hpp"
#include "SnRepresentationBank.hpp"
#include "SnFFTbank.hpp"

#include "Sn.hpp"
#include "SnOverSm.hpp"

namespace Snob2 {

class SnClasses {
public:
  SnClasses() {
    if (_snbank) {
      cout << "Only one SnClasses object can be defined." << endl;
      return;
    }
    _snbank = new SnBank();
    _snrepbank = new SnRepresentationBank();
  }

  ~SnClasses() {
    delete _snbank;
    delete _snrepbank;
  }
};

} // namespace Snob2
