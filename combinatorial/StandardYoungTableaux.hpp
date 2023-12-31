
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _StandardYoungTableaux
#define _StandardYoungTableaux

#include "CombinatorialBank.hpp"

namespace Snob2 {

class StandardYoungTableaux {
public:
  class iterator
      : public cnine::GenericIterator<StandardYoungTableaux, YoungTableau> {
  public:
    using GenericIterator::GenericIterator;
  };

  IntegerPartition p;
  const vector<YoungTableau *> *tableaux;
  bool is_view = false;

  ~StandardYoungTableaux() {
    if (!is_view) {
      for (auto p : *tableaux)
        delete p;
      delete tableaux;
    }
  }

public:
  StandardYoungTableaux(const IntegerPartition &_p) : p(_p) {
    tableaux = &_combibank->get_YoungTableaux(p);
    is_view = true;
  }

public: // Access
  int size() const { return tableaux->size(); }

  YoungTableau operator[](const int i) const { return *(*tableaux)[i]; }

  iterator begin() const { return iterator(this); }

  iterator end() const { return iterator(this, size()); }

public: // I/O
  string str(const string indent = "") const {
    return indent + "StandardYoungTableaux" + p.str();
  }

  friend ostream &operator<<(ostream &stream, const StandardYoungTableaux &x) {
    stream << x.str();
    return stream;
  }
};

} // namespace Snob2

#endif
