
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2022, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef _Transposition
#define _Transposition

#include "Snob2_base.hpp"

namespace Snob2{

  class Transposition{
  public:

    int i;
    int j;


  public:

    Transposition(const int _i): i(_i), j(_i+1){}

    Transposition(const int _i, const int _j): i(_i), j(_j){}


  public: 

    Transposition inv() const{
      return *this;
    }


  public: // I/O

    string str(const string indent="") const{
      return indent+"("+to_string(i)+","+to_string(j)+")";
    }
     
    
    friend ostream& operator<<(ostream& stream, const Transposition& x){
      stream<<x.str(); return stream;
    }


  };

}

#endif
