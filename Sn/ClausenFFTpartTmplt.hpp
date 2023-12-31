
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "ClausenFFTblockTmplt.hpp"
#include "SnVec.hpp"
#include "SnMultiVec.hpp"

namespace Snob2 {

class ClausenFFTpartTmplt {
public:
  int index = 0;
  int d = 0;
  int m = 0;
  int ioffs = 0;
  SnIrrepObj *irrep;
  vector<ClausenFFTblockTmplt *> blocks;

public
    : // ---- Constructors
      // -------------------------------------------------------------------------------
  ClausenFFTpartTmplt(const IntegerPartition &lambda, const int _index)
      : index(_index), irrep(_snbank->get_irrep(lambda)) {
    d = irrep->d;
  }

  ClausenFFTpartTmplt(const ClausenFFTpartTmplt &x) = delete;
  ClausenFFTpartTmplt &operator=(const ClausenFFTpartTmplt &x) = delete;

public
    : // ---- Access
      // -------------------------------------------------------------------------------------
  IntegerPartition get_lambda() const { return irrep->lambda; }

  void add(const ClausenFFTpartTmplt &sub) {
    blocks.push_back(new ClausenFFTblockTmplt(ioffs, m, sub.index));
    ioffs += sub.d;
    m += sub.m;
  }

public
    : // ---- Fourier transforms
      // -------------------------------------------------------------------------
  SnMultiPart uptransform(const SnMultiVec &v) const {
    SnMultiPart P(v.getN(), irrep, m, cnine::fill::zero);
    for (auto p : blocks) {
      P.add_to_block_multi(p->ioffs, p->joffs, *v.parts[p->subix]);
    }
    return P;
  }

public
    : // ---- I/O
      // ----------------------------------------------------------------------------------------
  string str(const string indent = "") const {
    ostringstream oss;
    oss << indent << "Part " << index << " " << irrep->lambda.str() << " ";
    oss << "(" << d << "," << m << ") ";
    oss << "" << endl; //" ("<<index<<")"<<endl;
    for (int i = 0; i < blocks.size(); i++) {
      oss << blocks[i]->str(indent + "  ");
    }
    return oss.str();
  }

  friend ostream &operator<<(ostream &stream, const ClausenFFTpartTmplt &x) {
    stream << x.str();
    return stream;
  }
};

} // namespace Snob2
