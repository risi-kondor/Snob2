#ifndef _IntegerPartitions
#define _IntegerPartitions

#include "CombinatorialBank.hpp"
#include "GenericIterator.hpp"


namespace Snob2{

  class IntegerPartitions{
  public:

    class iterator: public GenericIterator<IntegerPartitions,IntegerPartition>{
    public:
      using GenericIterator::GenericIterator;
    };


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

    IntegerPartition operator[](const int i) const{
      return *(*lambda)[i];
    }

    vector<IntegerPartition> operator()(const int first, const int last) const{
      vector<IntegerPartition> R;
      for(int i=first; i<=last; i++)
	R.push_back(*(*lambda)[i]);
      return R;
    }

    iterator begin() const{
      return iterator(this);
    }

    iterator end() const{
      return iterator(this,size());
    }
    
    

  };

}

#endif 
