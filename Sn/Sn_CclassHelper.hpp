
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef _Sn_CClassHelper
#define _Sn_CClassHelper

#include "SnObj.hpp"
#include "GenericIterator.hpp"


namespace Snob2{

  class Sn_CClassHelper{
  public:

    class iterator: public cnine::GenericIterator<Sn_CClassHelper,SnCClass>{
    public:
      using GenericIterator::GenericIterator;
    };


    const SnObj* obj;

    Sn_CClassHelper(const int n): obj(_snbank->get_Sn(n)){};

    Sn_CClassHelper(const SnObj* _obj): obj(_obj){};
        

    Sn_CClassHelper(const Sn_CClassHelper& x)=delete;
    Sn_CClassHelper& operator=(const Sn_CClassHelper& x)=delete;


  public:

    int size() const{
      return obj->ncclasses();
    }

    SnCClass operator()(const int i) const{
      return obj->cclass(i);
    }

    SnCClass operator[](const int i) const{
      return obj->cclass(i);
    }

    //SnCClass identity() const{
    //return obj->identity();
    //}

    iterator begin() const{
      return iterator(this);
    }

    iterator end() const{
      return iterator(this,size());
    }
    

  public:


  };

}

#endif


