// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _SnCGproduct
#define _SnCGproduct

#include "SnVec.hpp"
#include "SnWeights.hpp"
#include "SnCGbank.hpp"

namespace Snob2 {

void SnVec_addCGproduct(SnVec &R, const SnVec &x, const SnVec &y);

void SnVec_addCGproduct(SnVec &R, SnType &offs, const SnPart &x,
                        const SnPart &y) {
  const int n = x.getn();
  assert(y.getn() == n);

  if (n == 1) {
    int I = x.getm();
    int J = y.getm();
    for (int i = 0; i < I; i++)
      for (int j = 0; j < J; j++)
        R.parts[0]->inc(0, i * J + j, x(0, i) * y(0, j));
    offs[IntegerPartition({1})] += I * J;
  }

  SnVec xsub = SnVec::down(x);
  SnVec ysub = SnVec::down(y);

  SnVec sub =
      SnVec::zero(_sncgbank->CGproduct(xsub.get_type(), ysub.get_type()));
  SnVec_addCGproduct(sub, xsub, ysub);
  SnType sub_offs;

  SnCGfactors *F = _sncgbank->get_CGfactors(x.get_lambda(), y.get_lambda());
  for (auto p : *F) {
    const IntegerPartition &lamb = p.first;
    rtensor &target = *R.parts[lamb];
    int coffs = offs[lamb];
    int ncols = 0;
    int roffs = 0;
    for (auto q : p.second) {
      const IntegerPartition &mu = q.first;
      const rtensor &source = *sub.parts[mu];
      const rtensor &M = q.second;
      int nrows = source.dims(0);
      if (ncols == 0)
        ncols = M.dims(1);
      target.view2D_block(roffs, offs[lamb], nrows, ncols)
          .add_matmul_AA(source.view2D_block(0, sub_offs[mu], nrows, ncols),
                         M.view2D());
      roffs += nrows;
      sub_offs[mu] += ncols;
    }
    offs[lamb] += ncols;
  }
}

void SnVec_addCGproduct(SnVec &R, const SnVec &x, const SnVec &y) {
  SnType offs;
  for (auto p : x.parts)
    for (auto q : y.parts) {
      SnVec_addCGproduct(R, offs, *p, *q);
    }
}

} // namespace Snob2

#endif

/*
class SnCGproduct{
public:


public:

  SnVec operator()(const SnPart& x, const SnPart& y){
    SnVec R;
    return R;
  }

  SnVec operator()(const SnVec& x, const SnVec& y){
    SnVec R;
    return R;
  }



};
*/
