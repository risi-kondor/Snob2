
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _Sn_CharacterHelper
#define _Sn_CharacterHelper

//#include "SnObj.hpp"
#include "GenericIterator.hpp"
#include "SnCharacter.hpp"

namespace Snob2 {

class Sn_CharacterHelper {
public:
  class iterator
      : public cnine::GenericIterator<Sn_CharacterHelper, SnCharacter> {
  public:
    using GenericIterator::GenericIterator;
  };

  const SnObj *obj;
  SnCharBankLevel *level;

  Sn_CharacterHelper(const SnObj *_obj) : obj(_obj) {
    level = _sncharbank->get_level(obj->n);
  };

  Sn_CharacterHelper(const Sn_CharacterHelper &x) = delete;
  Sn_CharacterHelper &operator=(const Sn_CharacterHelper &x) = delete;

public:
  int size() const { // improve
    level->make_all_chars();
    return level->nchars();
  }

  SnCharacter operator[](const int i) const {
    level->make_all_chars();
    return SnCharacter(*level->get_character(i));
  }

  SnCharacter operator[](const IntegerPartition &lambda) const {
    // level->make_all_chars();
    return SnCharacter(*level->get_character(lambda));
  }

  iterator begin() const { return iterator(this); }

  iterator end() const { return iterator(this, size()); }

public:
};

} // namespace Snob2

#endif
