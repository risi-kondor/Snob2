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


  public: // operations

    SnElement operator*(const SnElement& y) const{
      return SnElement(this->Permutation::operator*(y));
    }

    SnElement inverse() const{
      return SnElement(Permutation::inverse());
    }

    SnElement inv() const{
      return inverse();
    }

  };

}

#endif
