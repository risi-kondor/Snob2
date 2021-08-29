#ifndef _Factorial
#define _Factorial 

#include "Snob2_base.hpp"



namespace Snob2{

  class factorial{
  public:
    static vector<int> fact;
    int value; 
    operator int(){
      return value;
    }
    factorial(const int n){
      if(n<fact.size()){value=fact[n]; return;}
      if(fact.size()==0) fact.push_back(1);
      int m=fact.size();
      fact.resize(n+1);
      for(int i=m; i<=n; i++)
	fact[i]=fact[i-1]*i;
      value=fact[n];
    }
  };

}

#endif
