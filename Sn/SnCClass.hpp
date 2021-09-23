#ifndef _SnCClass
#define _SnCClass

#include "IntegerPartition.hpp"

namespace Snob2{


  class SnCClass: public IntegerPartition{
  public:

    //IntegerPartition mu;



  public:

    SnCClass(const IntegerPartition& _mu):
      IntegerPartition(_mu){}


  public: // named constructors 

    //static SnCClass Identity(const int n){
    //return Permutation(n,cnine::fill_identity());
    //}


  public: // operations

    string str(const string indent="") const{
      return indent+"SnCClass"+IntegerPartition::str();
    }

    friend ostream& operator<<(ostream& stream, const SnCClass& x){
      stream<<x.str(); return stream;
    }

  };

}

#endif
