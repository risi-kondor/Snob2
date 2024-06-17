#ifndef _CombinatorialBank
#define _CombinatorialBank

#include "Snob2_base.hpp"
#include "CombinatorialBankLevel.hpp"


namespace Snob2{

  class CombinatorialBank{
  public:
    
    vector<CombinatorialBankLevel*> levels;
    
    ~CombinatorialBank(){
      for(auto p:levels) delete p;
    }

  public: 

    const vector<IntegerPartition*>& get_IntegerPartitions(const int n){
      CombinatorialBankLevel& l=level(n);
      return l.get_IntegerPartitions();
    }

    const vector<YoungTableau*>& get_YoungTableaux(const IntegerPartition& lambda){
      CombinatorialBankLevel& l=level(lambda.getn());
      return l.get_YoungTableaux(lambda);
    }

    const vector<IntegerPartition*>& get_ROpartitions(const int n){
      CombinatorialBankLevel& l=level(n);
      return l.get_ROpartitions();
    }


  private:

    CombinatorialBankLevel& level(const int n){
      if(n<=levels.size()) return *levels[n-1];
      const int _n=levels.size();
      levels.resize(n);
      for(int i=_n+1; i<=n; i++){
	if(i==1) levels[i-1]=new CombinatorialBankLevel();
	else levels[i-1]=new CombinatorialBankLevel(i,levels[i-2]);
      }
      return *levels[n-1];
    }

  };
  
}

#endif 
