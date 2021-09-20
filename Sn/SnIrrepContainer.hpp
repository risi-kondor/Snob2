#ifndef _SnIrrepContainer
#define _SnIrrepContainer

#include "SnObj.hpp"
#include "GenericIterator.hpp"

namespace Snob2{

  class SnIrrepContainer{
  public:

    class iterator: public GenericIterator<SnIrrepContainer,SnIrrep>{
    public:
      using GenericIterator::GenericIterator;
    };


    const SnObj* obj;

    SnIrrepContainer(const int n): obj(_snbank->get_Sn(n)){};

    SnIrrepContainer(const SnObj* _obj): obj(_obj){};
    

    

  public:

    int size() const{
      obj->make_all_irreps();
      return obj->irreps.size();
    }

    SnIrrep operator[](const int i) const{
      obj->make_all_irreps();
      return SnIrrep(obj->irreps[i]);
    }

    SnIrrep operator[](const IntegerPartition& lambda) const{
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
    /*
    class iterator{
    public:
      const SnIrrepContainer* owner;
      int i;

      iterator(const SnIrrepContainer* _owner, const int _i=0): 
	owner(_owner), i(_i){}

      int operator++(){++i; return i;}

      int operator++(int a){++i; return i-1;}

      SnIrrep operator*() const{
	return (*owner)[i];
      }
      
      bool operator==(const iterator& x) const{
	return i==x.i;
      }

      bool operator!=(const iterator& x) const{
	return i!=x.i;
      }

    };
    */

