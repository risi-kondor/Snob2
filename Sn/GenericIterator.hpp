
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef _GenericIterator
#define _GenericIterator

//#include "Snob2_base.hpp"

namespace Snob2{

  template<typename OWNER, typename OBJ>
  class GenericIterator{
  public:
    const OWNER* owner;
    int i;

    GenericIterator(const OWNER* _owner, const int _i=0): 
      owner(_owner), i(_i){}

    int operator++(){++i; return i;}

    int operator++(int a){++i; return i-1;}

    OBJ operator*() const{
      return (*owner)[i];
    }
      
    bool operator==(const GenericIterator& x) const{
      return i==x.i;
    }

    bool operator!=(const GenericIterator& x) const{
      return i!=x.i;
    }

  };


}

#endif
