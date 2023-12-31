
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "CombinatorialBank.hpp"
#include "GenericIterator.hpp"

namespace Snob2 {

extern CombinatorialBank *_combibank;

class IntegerPartitions {
public:
  class iterator
      : public cnine::GenericIterator<IntegerPartitions, IntegerPartition> {
  public:
    using GenericIterator::GenericIterator;
  };

  const int n;
  const vector<IntegerPartition *> *lambda;
  bool is_view = false;

  ~IntegerPartitions() {
    if (!is_view) {
      for (auto p : *lambda)
        delete p;
      delete lambda;
    }
  }

public: // Constructors
  IntegerPartitions(const int _n, const vector<IntegerPartition *> *_lambda,
                    bool _is_view)
      : n(_n), lambda(_lambda), is_view(_is_view) {}

  IntegerPartitions(const int _n) : n(_n) {
    lambda = &_combibank->get_IntegerPartitions(n);
    is_view = true;
  }

public: // Named constructors
  static IntegerPartitions RestrictionOrdered(const int _n) {
    return IntegerPartitions(_n, &_combibank->get_ROpartitions(_n), true);
  }

public: // Access
  int size() const { return lambda->size(); }

  IntegerPartition operator[](const int i) const { return *(*lambda)[i]; }

  vector<IntegerPartition> operator()(const int first, const int last) const {
    vector<IntegerPartition> R;
    for (int i = first; i <= last; i++)
      R.push_back(*(*lambda)[i]);
    return R;
  }

  iterator begin() const { return iterator(this); }

  iterator end() const { return iterator(this, size()); }

  // vector<IntegerPartition> restriction_poset_ordered(){
  // return _combibank->restriction_post_ordered_partitions();
  // }
};

} // namespace Snob2
