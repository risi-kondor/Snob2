
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _SnProductRepresentation

#define _SnProductRepresentation

#include <map>

//#include "IntegerPartition.hpp"
#include "SnIrrep.hpp"
//#include "SnType.hpp"
#include "SnBank.hpp"

#include "Rtensor4_view.hpp"

namespace Snob2 {

template <class RHO0, class RHO1> class SnProductRepresentation {
public:
  int d;
  int d0;
  int d1;

  const RHO0 &rho0;
  const RHO1 &rho1;

  SnProductRepresentation(const RHO0 &_rho0, const RHO1 &_rho1)
      : rho0(_rho0), rho1(_rho1) {
    d0 = rho0.dim();
    d1 = rho1.dim();
    d = rho0.dim() * rho1.dim();
  }

public:
  int dim() const { return d; }

public:
  rtensor JucysMurphy(const int k) {
    rtensor R(cnine::dims(d, d), cnine::fill::zero);
    rtensor A(cnine::dims(d, d), cnine::fill::identity);
    for (int i = k - 1; i >= 1; i--) {
      apply_transp(split0(A.view2(), 1, d), i);
      rtensor B(A);
      apply(split0(B.view2(), 1, d), ContiguousCycle(k, i + 1));
      R += B;
    }
    return R;
  }

public
    : // ---- In-place operations
      // ------------------------------------------------------------------------
  void apply(const cnine::Rtensor3_view &A, const int tau) const {
    rho0.apply_transp(split1(A, d0, d1).fuse23(), tau);
    rho1.apply_transp(split1(A, d0, d1).fuse01(), tau);
  }

  void apply_transp(const cnine::Rtensor3_view &A, const int tau) const {
    rho0.apply_transp(split1(A, d0, d1).fuse23(), tau);
    rho1.apply_transp(split1(A, d0, d1).fuse01(), tau);
  }

  void apply(const cnine::Rtensor3_view &A, const ContiguousCycle &cyc) const {
    rho0.apply(split1(A, d0, d1).fuse23(), cyc);
    rho1.apply(split1(A, d0, d1).fuse01(), cyc);
  }
};

inline SnProductRepresentation<SnIrrep, SnIrrep> operator*(SnIrrep &rho0,
                                                           SnIrrep &rho1) {
  return SnProductRepresentation<SnIrrep, SnIrrep>(rho0, rho1);
}

} // namespace Snob2

#endif
