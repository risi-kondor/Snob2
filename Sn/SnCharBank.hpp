#ifndef _SnCharBank
#define _SnCharBank

#include "SnClassFunction.hpp"
#include "SnObj.hpp"
#include "indexed_map.hpp"


namespace Snob2{

  class SnCharBankLevel{
  public:

    int n;

    //unordered_map<IntegerPartition,SnClassFunction*> characters;
    indexed_map<IntegerPartition,SnClassFunction> chars;
    

  public:

    SnCharBankLevel(const int _n): n(_n){}

    SnClassFunction* get_character(const IntegerPartition& lambda){
      assert(lambda.getn()==n);
      //auto it=characters.find(lambda);
      //if(it!=characters.end()) return it->second;
      if(chars.exists(lambda)) return chars[lambda];

      SnClassFunction* chi=new SnClassFunction(n,cnine::fill_raw()); //T
      SnObj* G=_snbank->get_Sn(n);
      SnIrrepObj* rho=_snbank->get_irrep(lambda);
      for(int i=0; i<chi->size(); i++)
	chi->set_value(i,rho->character(G->cclass(i)));
      //characters[lambda]=chi;
      chars.insert(lambda,chi);
      return chi;
    }
    
    SnClassFunction* get_character(const int i){
      return chars[i];
    }

    void make_all_chars(){
      IntegerPartitions Lambda(n);
      for(auto p:Lambda)
	get_character(p);
    }

    int nchars(){
      return chars.size();
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

    SnCharBankLevel* get_level(const int n){
      if(n-1<levels.size()) return levels[n-1];
      const int _n=levels.size();
      levels.resize(n);
      for(int i=_n+1; i<=n; i++){
	levels[i-1]=new SnCharBankLevel(i);
      }
      return levels[n-1];
    }


  public:


  };

}

#endif
