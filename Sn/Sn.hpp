#ifndef _Sn
#define _Sn

#include "SnBank.hpp"
#include "SnElement.hpp"
#include "SnIrrep.hpp"


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

    SnIrrep irrep(const IntegerPartition& lambda){
      return SnIrrep(obj->get_irrep(lambda));
    }

    vector<SnIrrep> all_irreps() const{
      vector<SnIrrepObj*> objs=obj->get_all_irreps();
      vector<SnIrrep> R(objs.size());
      for(int i=0; i<objs.size(); i++)
	R[i]=SnIrrep(objs[i]);
      return R;
    }

    
  public:

    string str(const string indent="") const{
      return "Sn("+to_string(n)+")";
    }

    friend ostream& operator<<(ostream& stream, const Sn& x){
      stream<<x.str(); return stream;
    }


  };

}

#endif 
