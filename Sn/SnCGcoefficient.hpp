#ifndef _SnCGcoefficient
#define _SnCGcoefficient

#include "SnCGbank.hpp"


namespace Snob2{

  class SnCGcoefficient{
  public:

    int v;

    SnCGcoefficient(const IntegerPartition& mu1, const IntegerPartition& mu2, const IntegerPartition& mu3){
      v=_sncgbank->coeff(mu1,mu2,mu3);
    }

  public:

    operator int() const{
      return v;
    }

  };

}

#endif
