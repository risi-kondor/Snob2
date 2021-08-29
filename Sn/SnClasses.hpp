#ifndef _SnClasses
#define _SnClasses

#include "Snob2_base.hpp"
#include "SnBank.hpp"

#include "Sn.hpp"
#include "SnOverSm.hpp"


namespace Snob2{

  class SnClasses{
  public:

    SnClasses(){
      if(_snbank){cout<<"Only one SnClasses object can be defined."<<endl; return;}
      _snbank=new SnBank();
    }
    
    ~SnClasses(){
      delete _snbank;
    }

  };

}

#endif 
