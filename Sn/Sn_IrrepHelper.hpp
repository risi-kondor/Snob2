
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "SnObj.hpp"
#include "GenericIterator.hpp"

namespace Snob2 {

class Sn_IrrepHelper {
public:
  class iterator : public cnine::GenericIterator<Sn_IrrepHelper, SnIrrep> {
  public:
    using GenericIterator::GenericIterator;
  };

  const SnObj *obj;

  Sn_IrrepHelper(const int n) : obj(_snbank->get_Sn(n)){};

  Sn_IrrepHelper(const SnObj *_obj) : obj(_obj){};

  Sn_IrrepHelper(const Sn_IrrepHelper &x) = delete;
  Sn_IrrepHelper &operator=(const Sn_IrrepHelper &x) = delete;

public:
  int size() const {
    obj->make_all_irreps();
    return obj->irreps.size();
  }

  SnIrrep operator()(const int i) const {
    obj->make_all_irreps();
    return SnIrrep(obj->irreps[i]);
  }

  SnIrrep operator[](const int i) const {
    obj->make_all_irreps();
    return SnIrrep(obj->irreps[i]);
  }

  SnIrrep operator[](const IntegerPartition &lambda) const {
    obj->make_all_irreps();
    return SnIrrep(obj->get_irrep(lambda));
  }

  SnIrrep operator()(const IntegerPartition &lambda) const {
    obj->make_all_irreps();
    return SnIrrep(obj->get_irrep(lambda));
  }

  iterator begin() const { return iterator(this); }

  iterator end() const { return iterator(this, size()); }

public:
};

} // namespace Snob2
