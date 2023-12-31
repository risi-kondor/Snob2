
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "Snob2_base.cpp"
#include "Snob2_session.hpp"
#include "SnClasses.hpp"
#include "FunctionOnGroup.hpp"
#include "RtensorObj.hpp"
//#include "Gdims.hpp"
#include "SnVec.hpp"
#include "CombinatorialClasses.hpp"

using namespace cnine;
using namespace Snob2;

// typedef CscalarObj cscalar;
// typedef CtensorObj ctensor;

int main(int argc, char **argv) {
  Snob2_session session;
  SnClasses Snclasses;
  CombinatorialClasses combi_classes;
  cout << endl;

  Sn G(4);
  FunctionOnGroup<Sn, cnine::RtensorObj> f(G, cnine::fill::gaussian);
  cout << f << endl;

  SnVec v = SnVec::Fourier(f);
  printl("v", v);
}
