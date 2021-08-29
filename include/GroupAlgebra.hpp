#ifndef _GroupAlgebra
#define _GroupAlgebra

#include "Group.hpp"

namespace Snob2{

  template<typename GROUP, typename TENSOR>
  class GroupAlgebra{
  public:

    typedef cnine::Gdims Gdims;

    const GROUP& G; 
    Gdims dims;

  public:

    
    GroupAlgebra(const GROUP& _G, const Gdims& _dims):
      //TENSOR(_dims.prepend(_G.size(),dummy)),
      G(_G),
      dims(_dims){
    }


  public: // I/O

    string str(const string indent="") const{
      return "Algebra<"+G.str()+">["+dims.str()+"]";
    }

    friend ostream& operator<<(ostream& stream, const GroupAlgebra& x){
      stream<<x.str(); return stream;
    }


  };

}

#endif
