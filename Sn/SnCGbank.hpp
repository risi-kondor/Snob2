#ifndef _SnCGbank
#define _SnCGbank

#include "SnWeights.hpp"

namespace Snob2{

  class SnCGbank{
  public:

    unordered_map<pair<IntegerPartition,IntegerPartition>,SnWeights*> tables;

  public:

    SnWeights* get(const IntegerPartition& lambda1, const IntegerPartition& lambda2){
      pair<IntegerPartition,IntegerPartition> lambdas(lambda1,lambda2);
      auto it=tables.find(lambdas);
      if(it!=tables.end()) return it->second;
      SnWeights* table=nullptr; //new SnWeights(lambdas); // TODO
      tables[lambdas]=table;
      return table;
    }


  public:


  };

}

#endif
