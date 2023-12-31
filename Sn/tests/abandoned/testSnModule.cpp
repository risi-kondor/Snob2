
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "Snob2_base.cpp"
#include "Snob2_session.hpp"
#include "CombinatorialClasses.hpp"
#include "SnClasses.hpp"
#include "SnModule.hpp"

using namespace cnine;
using namespace Snob2;

// typedef CscalarObj cscalar;
// typedef CtensorObj ctensor;

int main(int argc, char **argv) {

  Snob2_session session;
  CombinatorialClasses combi_classes;
  SnClasses Snclasses;
  cout << endl;

  SnModule type0(IntegerPartition({4, 2}), 1);
  type0.set(IntegerPartition({5, 1}), 2);

  cout << type0 << endl;
}
