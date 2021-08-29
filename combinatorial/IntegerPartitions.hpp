#ifndef _IntegerPartitions
#define _IntegerPartitions

#include "CombinatorialBank.hpp"


namespace Snob2{

  class IntegerPartitions{
  public:

    const int n;
    const vector<IntegerPartition*>* lambda;
    bool is_view=false;

    ~IntegerPartitions(){
      if(!is_view){
	for(auto p:*lambda) delete p;
	delete lambda;
      }
    }

  public: // Constructors 

    IntegerPartitions(const int _n): n(_n){
      lambda=&_combibank->get_IntegerPartitions(n);
      is_view=true;
    }


  public: // Access

    int size() const{
      return lambda->size();
    }

    IntegerPartition operator[](const int i){
      return *(*lambda)[i];
    }

  };

}

#endif 
