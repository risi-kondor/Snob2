#ifndef _Sn_ElementHelper
#define _Sn_ElementHelper

#include "SnObj.hpp"
#include "GenericIterator.hpp"


namespace Snob2{

  class Sn_ElementHelper{
  public:

    class iterator: public GenericIterator<Sn_ElementHelper,SnElement>{
    public:
      using GenericIterator::GenericIterator;
    };


    const SnObj* obj;

    Sn_ElementHelper(const int n): obj(_snbank->get_Sn(n)){};

    Sn_ElementHelper(const SnObj* _obj): obj(_obj){};
        

    Sn_ElementHelper(const Sn_ElementHelper& x)=delete;
    Sn_ElementHelper& operator=(const Sn_ElementHelper& x)=delete;


  public:

    int size() const{
      return obj->size();
    }

    SnElement operator()(const int i) const{
      return obj->element(i);
    }

    SnElement operator[](const int i) const{
      return obj->element(i);
    }

    SnElement identity() const{
      return obj->identity();
    }

    SnElement random() const{
      return obj->random();
    }

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


