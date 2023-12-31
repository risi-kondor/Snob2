
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
#include "SnPart.hpp"

#include "SnCGbank.hpp"
#include "SnCGcoefficient.hpp"
// class SnCGbank
// SnCGbank* _sncgbank=nullptr;

//#include "SnPartProduct.hpp"
//#include "SnCGproduct.hpp"

using namespace cnine;
using namespace Snob2;

// typedef CscalarObj cscalar;
typedef RtensorObj rtensor;

int main(int argc, char **argv) {

  Snob2_session session;

  int n = 6;
  Sn G(n);
  IntegerPartition lambda({n - 2, 2});

  cout << SnCGcoefficient(lambda, lambda, {n - 1, 1}) << endl << endl;

  SnPart x = SnPart::gaussian(lambda, 1);
  printl("x", x);

  SnPart y = SnPart::gaussian(lambda, 1);
  printl("y", y);

  SnVec z = _sncgbank->CGproduct(x, y);

  cout << "-----------------------------------------------------" << endl;
  printl("z", z);

  Transposition tau(n - 1);

  SnPart xr = x.apply(tau);
  SnPart yr = y.apply(tau);
  printl("zr", _sncgbank->CGproduct(xr, yr));
  printl("zrr", z.apply(tau));

  /*
  SnVec C=SnPartProduct(A,B);
  printl("C",C);

  SnElement sigma=G.random();
  auto Ad=sigma*A;
  auto Bd=sigma*B;
  SnVec Cd=SnPartProduct(Ad,Bd);
  printl("Cd",Cd);

  auto Cdd=sigma*C;
  printl("Cdd",Cdd);
  */
}
// cout<<*_sncgbank->get_CGfactors(lambda,lambda)<<endl;
