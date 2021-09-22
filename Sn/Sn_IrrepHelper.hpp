#ifndef _Sn_IrrepHelper
#define _Sn_IrrepHelper

#include "SnObj.hpp"
#include "GenericIterator.hpp"


namespace Snob2{

  class Sn_IrrepHelper{
  public:

    class iterator: public GenericIterator<Sn_IrrepHelper,SnIrrep>{
    public:
      using GenericIterator::GenericIterator;
    };


    const SnObj* obj;

    Sn_IrrepHelper(const int n): obj(_snbank->get_Sn(n)){};

    Sn_IrrepHelper(const SnObj* _obj): obj(_obj){};

    Sn_IrrepHelper(const Sn_IrrepHelper& x)=delete;
    Sn_IrrepHelper& operator=(const Sn_IrrepHelper& x)=delete;
        

  public:

    int size() const{
      obj->make_all_irreps();
      return obj->irreps.size();
    }

    SnIrrep operator()(const int i) const{
      obj->make_all_irreps();
      return SnIrrep(obj->irreps[i]);
    }

    SnIrrep operator[](const int i) const{
      obj->make_all_irreps();
      return SnIrrep(obj->irreps[i]);
    }

    SnIrrep operator[](const IntegerPartition& lambda) const{
      obj->make_all_irreps();
      return SnIrrep(obj->get_irrep(lambda));
    }

    SnIrrep operator()(const IntegerPartition& lambda) const{
      obj->make_all_irreps();
      return SnIrrep(obj->get_irrep(lambda));
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



