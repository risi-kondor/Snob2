
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _CombinatorialClasses
#define _CombinatorialClasses

#include "Snob2_base.hpp"
#include "CombinatorialBank.hpp"

#include "IntegerPartition.hpp"
#include "YoungTableau.hpp"
//#include "StandardYoungTableau.hpp"

#include "IntegerPartitions.hpp"
#include "YoungTableaux.hpp"
#include "StandardYoungTableaux.hpp"

namespace Snob2 {

class CombinatorialClasses {
public:
  CombinatorialClasses() {
    if (_combibank) {
      cout << "Only one CombinatorialClasses object can be defined." << endl;
      return;
    }
    _combibank = new CombinatorialBank();
  }

  ~CombinatorialClasses() { delete _combibank; }
};

} // namespace Snob2

#endif
