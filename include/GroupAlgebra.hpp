
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _GroupAlgebra
#define _GroupAlgebra

#include "Group.hpp"

namespace Snob2 {

template <typename GROUP, typename TENSOR> class GroupAlgebra {
public:
  typedef cnine::Gdims Gdims;

  const GROUP &G;
  Gdims dims;

public:
  GroupAlgebra(const GROUP &_G, const Gdims &_dims)
      : // TENSOR(_dims.prepend(_G.size(),dummy)),
        G(_G), dims(_dims) {}

public: // I/O
  string str(const string indent = "") const {
    return "Algebra<" + G.str() + ">[" + dims.str() + "]";
  }

  friend ostream &operator<<(ostream &stream, const GroupAlgebra &x) {
    stream << x.str();
    return stream;
  }
};

} // namespace Snob2

#endif
