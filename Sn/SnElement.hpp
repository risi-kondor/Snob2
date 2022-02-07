
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef _SnElement
#define _SnElement

#include "Permutation.hpp"

namespace Snob2{


  class SnElement: public Permutation{
  public:

    using Permutation::Permutation;


  public: // conversions 

    SnElement(const Permutation& x):
      Permutation(x){}

    SnElement(const int n, const Transposition& x):
      Permutation(n,x){}


  public: // named constructors 

    static SnElement Identity(const int n){
      return Permutation(n,cnine::fill_identity());
    }

    static SnElement transposition(const int n, const int i, const int j){
      return Permutation::transposition(n,i,j);
    }

    static SnElement contiguous_cycle(const int n, const int i, const int j){
      return Permutation::contiguous_cycle(n,i,j);
    }


  public: // operations

    SnElement operator*(const SnElement& y) const{
      return SnElement(this->Permutation::operator*(y));
    }

    SnElement inverse() const{
      return SnElement(Permutation::inverse());
    }

    SnElement inv() const{
      return inverse();
    }

  };

}

#endif
