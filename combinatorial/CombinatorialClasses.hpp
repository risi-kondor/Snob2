#ifndef _CombinatorialClasses
#define _CombinatorialClasses

#include "Snob2_base.hpp"
#include "CombinatorialBank.hpp"

#include "IntegerPartition.hpp"
#include "YoungTableau.hpp"

#include "IntegerPartitions.hpp"
#include "YoungTableaux.hpp"


namespace Snob2{

  class CombinatorialClasses{
  public:

    CombinatorialClasses(){
      if(_snbank){cout<<"Only one CombinatorialClasses object can be defined."<<endl; return;}
      _combibank=new CombinatorialBank();
    }
    
    ~CombinatorialClasses(){
      delete _combibank;
    }

  };

}

#endif 
