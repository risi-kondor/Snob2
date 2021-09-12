#ifndef _CombinatorialClasses
#define _CombinatorialClasses

#include "Snob2_base.hpp"
#include "CombinatorialBank.hpp"

#include "IntegerPartition.hpp"
#include "YoungTableau.hpp"
//#include "StandardYoungTableau.hpp"

#include "IntegerPartitions.hpp"
#include "YoungTableaux.hpp"
#include "StandardYoungTableaux.hpp"


namespace Snob2{

  class CombinatorialClasses{
  public:

    CombinatorialClasses(){
      if(_combibank){cout<<"Only one CombinatorialClasses object can be defined."<<endl; return;}
      _combibank=new CombinatorialBank();
    }
    
    ~CombinatorialClasses(){
      delete _combibank;
    }

  };

}

#endif 
