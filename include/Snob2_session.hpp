
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef _Snob2_session
#define _Snob2_session

#include "CnineSession.hpp"
#include "Snob2_base.hpp"
#include "CombinatorialClasses.hpp"

#include "SnBank.hpp"
#include "SnRepresentationBank.hpp"
#include "Sn.hpp" // eliminate this
#include "SnFFTbank.hpp"
//#include "SnCGbank.hpp"
//#include "SnClasses.hpp"


namespace Snob2{

  class Snob2_session{
  public:

    cnine::cnine_session* cnine_session=nullptr;


    Snob2_session(){

      cnine_session=new cnine::cnine_session();

      if(_combibank){cout<<"Only one CombinatorialClasses object can be defined."<<endl; return;}
      _combibank=new CombinatorialBank();

      if(_snbank){cout<<"Only one SnClasses object can be defined."<<endl; return;}
      _snbank=new SnBank();

      _snrepbank=new SnRepresentationBank();

      _snfftbank=new SnFFTbank();

      _sncharbank=new SnCharBank();

      //_sncgbank=new SnCGbank();

      cout<<"Snob2 initialized."<<endl<<endl;

    }


    ~Snob2_session(){
      cout<<endl<<"Shutting down Snob2."<<endl;
      delete cnine_session;
    }
    
  };

}


#endif 
