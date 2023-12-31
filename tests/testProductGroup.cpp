
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "GElib_base.cpp"
#include "GElibSession.hpp"
#include "GroupClasses.hpp"

using namespace cnine;
using namespace GElib;

int main(int argc, char **argv) {
  GElibSession session;
  cout << endl;

  CyclicGroup G1(3);
  CyclicGroup G2(4);

  // ProductGroup<CyclicGroup,CyclicGroup> G(G1,G2);
  auto G = G1 * G2;

  cout << G.identity() << endl << endl;

  for (int i = 0; i < G.size(); i++)
    cout << G.element(i) << endl;
}
