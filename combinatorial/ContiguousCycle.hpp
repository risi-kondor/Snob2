#ifndef _ContiguousCycle
#define _ContiguousCycle

#include "Snob2_base.hpp"

namespace Snob2{

  class ContiguousCycle{
  public:

    int a;
    int b;


  public:

    ContiguousCycle(const int _a, const int _b): a(_a), b(_b){}


  public: // I/O

    string str(const string indent="") const{
      return indent+"CCycle("+to_string(a)+","+to_string(b)+")";
    }
     
    
    friend ostream& operator<<(ostream& stream, const ContiguousCycle& x){
      stream<<x.str(); return stream;
    }


  };

}

#endif
