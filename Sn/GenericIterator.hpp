#ifndef _GenericIterator
#define _GenericIterator

#include "Snob2_base.hpp"

namespace Snob2{

  template<typename OWNER, typename OBJ>
  class GenericIterator{
  public:
    const OWNER* owner;
    int i;

    GenericIterator(const OWNER* _owner, const int _i=0): 
      owner(_owner), i(_i){}

    int operator++(){++i; return i;}

    int operator++(int a){++i; return i-1;}

    OBJ operator*() const{
      return (*owner)[i];
    }
      
    bool operator==(const GenericIterator& x) const{
      return i==x.i;
    }

    bool operator!=(const GenericIterator& x) const{
      return i!=x.i;
    }

  };


}

#endif
