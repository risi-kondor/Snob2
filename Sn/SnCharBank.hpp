#ifndef _SnCharBank
#define _SnCharBank

#include "SnClassFunction.hpp"


namespace Snob2{

  class SnCharBankLevel{
  public:

    unordered_map<IntegerPartition,SnClassFunction*> characters;

  public:

    SnCharBankLevel(const int _n){}

    SnClassFunction* get_character(const IntegerPartition& lambda){
      auto it=characters.find(lambda);
      if(it!=characters.end()) return it->second;
      SnClassFunction* chi=new SnClassFunction(lambda.getn(),cnine::fill::zero); //T
      characters[lambda]=chi;
      return chi;
    }
    

  };


  class SnCharBank{
  public:

    vector<SnCharBankLevel*> levels;

    ~SnCharBank(){
      for(auto p: levels) delete p;
    }


  public:

    SnClassFunction* get_character(const IntegerPartition& lambda){
      const int n=lambda.getn();
      if(n-1<levels.size()) return levels[n-1]->get_character(lambda);
      const int _n=levels.size();
      levels.resize(n);
      for(int i=_n+1; i<=n; i++){
	levels[i-1]=new SnCharBankLevel(i);
      }
      return levels[n-1]->get_character(lambda);
    }

  public:


  };

}

#endif
