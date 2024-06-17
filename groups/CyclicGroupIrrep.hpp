
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef _CyclicGroupIrrep
#define _CyclicGroupIrrep

//#include "CtensorObj.hpp"

#include "Group.hpp"
#include "CyclicGroupElement.hpp"


namespace Snob2{

  class CyclicGroupIrrep: public Girrep{
  public:

    typedef cnine::Gdims Gdims;
    //typedef cnine::CtensorObj ctensor;


    CyclicGroupIrrep(const int _n, const int _k):
      Girrep(new CyclicGroupIrrepObj(_n,_k)){}

  public: // I/O

    string classname() const{
      return "CyclicGroupIrrep";
    }


  };

}

#endif
