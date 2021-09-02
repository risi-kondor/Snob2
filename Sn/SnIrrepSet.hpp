#ifndef _SnIrrepSet
#define _SnIrrepSet

#include "SnIrrepObj.hpp"

namespace Snob2{

  class SnIrrepSet{
  public:

    const SnIrrepObj* obj;
    IntegerPartition lambda;

  public:

    SnIrrep(const SnIrrepObj* _obj):
      obj(_obj), lambda(_obj->lambda){}

  };

}

#endif
