#ifndef _Sn
#define _Sn

#include "SnBank.hpp"
#include "SnElement.hpp"


namespace Snob2{

  class Sn{
  public:

    const int n;
    SnObj* obj;

    Sn(const int _n): n(_n){
      obj=_snbank->get_Sn(n);
    }

    static SnElement dummy_element(){return SnElement::Identity(1);}


  public: // Access

    int size() const{
      return obj->order;
    }

    int get_order() const{
      return obj->order;
    }

    SnElement identity() const{
      return SnElement(n,cnine::fill_identity());
    }

    SnElement element(const int i) const{
      return obj->element(i);
    }

    int index(const SnElement& sigma) const{
      return obj->index(sigma);
    }

  };

}

#endif 
