#ifndef _SnElement
#define _SnElement

#include "Permutation.hpp"

namespace Snob2{


  class SnElement: public Permutation{
  public:

    using Permutation::Permutation;


  public: // conversions 

    SnElement(const Permutation& x):
      Permutation(x){}


  public: // named constructors 

    static SnElement Identity(const int n){
      return Permutation(n,cnine::fill_identity());
    }


  };

}

#endif
