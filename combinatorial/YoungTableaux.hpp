
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _YoungTableaux
#define _YoungTableaux

#include "CombinatorialBank.hpp"

namespace Snob2 {

class YoungTableaux {
public:
  class iterator : public cnine::GenericIterator<YoungTableaux, YoungTableau> {
  public:
    using GenericIterator::GenericIterator;
  };

  IntegerPartition p;
  const vector<YoungTableau *> *tableaux;
  bool is_view = false;

  ~YoungTableaux() {
    if (!is_view) {
      for (auto p : *tableaux)
        delete p;
      delete tableaux;
    }
  }

public:
  YoungTableaux(const IntegerPartition &_p) : p(_p) {
    tableaux = &_combibank->get_YoungTableaux(p);
    is_view = true;
  }

public: // Access
  int size() const { return tableaux->size(); }

  YoungTableau operator[](const int i) { return *(*tableaux)[i]; }

  iterator begin() const { return iterator(this); }

  iterator end() const { return iterator(this, size()); }
};

} // namespace Snob2

#endif
