
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#include "Cnine_base.cpp"
#include "Snob2_base.hpp"

#include "Factorial.hpp"
//#include "Dprogram.hpp"

/*
#include "SO3part_ops.hpp"
#include "SO3vec_ops.hpp"
#include "SO3vec_add_ops.hpp"
#include "SO3vec_add_inp_ops.hpp"
#include "SO3vec_CGproduct_ops.hpp"
*/

//#include "SnCGbank.hpp"


//vector<int> Snob2::factorial::fact;


namespace Snob2{

  class CombinatorialBank;
  CombinatorialBank* _combibank=nullptr;

  class SnBank;
  SnBank* _snbank=nullptr;

  class SnRepresentationBank;
  SnRepresentationBank* _snrepbank=nullptr;

  class SnFFTbank;
  SnFFTbank* _snfftbank=nullptr;

  class SnCharBank;
  SnCharBank* _sncharbank=nullptr;

  class SnCGbank;
  SnCGbank* _sncgbank=nullptr;

}


