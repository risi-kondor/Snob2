
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "GElib_base.cpp"
#include "GElibSession.hpp"
#include "CombinatorialClasses.hpp"

using namespace cnine;
using namespace GElib;

// typedef CscalarObj cscalar;
// typedef CtensorObj ctensor;

int main(int argc, char **argv) {
  GElibSession session;
  CombinatorialClasses combi_classes;
  cout << endl;

  IntegerPartition lambda({4, 3, 1});
  YoungTableau t(lambda);
  cout << t << endl;

  YoungTableaux T(IntegerPartition({2, 2, 1}));
  for (int i = 0; i < T.size(); i++)
    cout << T[i] << endl;
}
