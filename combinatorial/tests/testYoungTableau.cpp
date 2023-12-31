
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "Snob2_base.cpp"
#include "Snob2_session.hpp"

using namespace cnine;
using namespace Snob2;

int main(int argc, char **argv) {
  Snob2_session session;

  IntegerPartition lambda({4, 3, 1});
  YoungTableau t(lambda);
  cout << t << endl;

  StandardYoungTableaux T(IntegerPartition({2, 2, 1}));
  for (int i = 0; i < T.size(); i++)
    cout << T[i] << endl;

  for (auto p : T)
    cout << p << endl;
}
