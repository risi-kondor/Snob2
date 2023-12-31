
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "SnVec.hpp"
#include "SnWeights.hpp"

namespace Snob2 {

class SnPartProduct {
public:
  int n;

  const SnPart &x;
  const SnPart &y;

public
    : // ---- Constructors
      // -------------------------------------------------------------------------------
  SnPartProduct(const SnPart &_x, const SnPart &_y) : x(_x), y(_y) {
    n = x.getn();
    // cout<<"n="<<n<<endl;
  };

public
    : // ---- CG-product
      // ---------------------------------------------------------------------------------
  operator SnVec() const {
    if (n == 1) {
      return SnVec(new SnPart(_snbank->get_irrep({1}), x(0, 0) * y(0, 0)));
    }

    SnVec xsub = SnVec::down(x);
    SnVec ysub = SnVec::down(y);

    // cout<<xsub<<endl;
    // return SnVec();

    SnVec sub =
        SnVec::zero(_sncgbank->CGproduct(xsub.get_type(), ysub.get_type()));
    vector<SnVec> subs;
    for (auto p : xsub.parts)
      for (auto q : ysub.parts) {
        // cout<<"<"<<p->irrep->lambda<<","<<q->irrep->lambda<<">"<<endl;
        subs.push_back(SnVec(SnPartProduct(*p, *q)));
      }
    SnVec sub = SnVec::cat(subs);
    cout << sub << endl << "----" << endl;
    SnType *tau = _sncgbank->get_type(x.get_lambda(), y.get_lambda());
    SnWeights *W = _sncgbank->getW(x.get_lambda(), y.get_lambda());
    return SnVec::up(*tau, (*W) * sub);
    * / return xsub;
  }

public:
};

} // namespace Snob2
