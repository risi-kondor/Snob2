#ifndef _SnBank
#define _SnBank

#include "Snob2_base.hpp"
#include "SnObj.hpp"
//#include "IntegerPartitionsObj.hpp"

namespace Snob2{


  class SnBank{
  public:
    
    vector<SnObj*> sn;
    

  public: 

    SnObj* get_Sn(const int n){
      if(n-1<sn.size()) return sn[n-1];
      const int _n=sn.size();
      sn.resize(n);
      for(int i=_n+1; i<=n; i++){
	sn[i-1]=new SnObj(i);
	if(i>1) sn[i-1]->Snminus1=sn[i-2];
      }
      return sn[n-1];
    }

    SnIrrepObj* get_irrep(const IntegerPartition& lambda){
      return get_Sn(lambda.getn())->get_irrep(lambda);
    }
    
  public: 


  };
  

}

#endif 
