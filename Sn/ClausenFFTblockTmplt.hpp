
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef _ClausenFFTblockTmplt
#define _ClausenFFTblockTmplt

#include "Snob2_base.hpp"

namespace Snob2{

  class ClausenFFTblockTmplt{
  public:

    int ioffs;
    int joffs;
    int subix;

  public:

    ClausenFFTblockTmplt(const int _ioffs, const int _joffs, const int _subix):
      ioffs(_ioffs), joffs(_joffs), subix(_subix){}

  public:

    string str(const string indent="") const{
      ostringstream oss;
      oss<<indent<<"Block ("<<ioffs<<","<<joffs<<") <-"<<subix<<endl;
      return oss.str();
    }


    friend ostream& operator<<(ostream& stream, const ClausenFFTblockTmplt& x){
      stream<<x.str(); return stream;
    }



  };


}

#endif
