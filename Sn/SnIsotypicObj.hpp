#ifndef _SnIsotypicObj
#define _SnIsotypicObj

#include "SnIrrepObj.hpp"

namespace Snob2{

  class SnIsotypicObj{
  public:

    const SnIrrepObj* irrep;
    vector<SnIsotypicObj*> subs;
    int m;


  public:

    SnIsotypicObj(){}

    SnIsotypicObj(const SnIrrepObj* _irrep, int _m=0): 
      irrep(_irrep), m(_m){}


  public: 

    string str(const string indent="") const{
      ostringstream oss;
      oss<<""<<irrep->lambda<<":"<<m<<"";
      return oss.str();
    }

    friend ostream& operator<<(ostream& stream, const SnIsotypicObj& x){
      stream<<x.str(); return stream;
    }


  };

}

#endif
