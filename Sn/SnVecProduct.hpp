#ifndef _SnVecProduct
#define _SnVecProduct

#include "SnVec.hpp"

namespace Snob2{

  class SnVecProduct{
  public:

    SnVec& x;
    SnVec& y;


  public: // ---- Constructors -------------------------------------------------------------------------------

    
    SnVecProduct(const SnVec& _x, const SnVec& _y): x(_x), y(_y){};


  public: // ---- CG-product ---------------------------------------------------------------------------------

    
    operator SnVec() const{
      
    }

  };

}

#endif
