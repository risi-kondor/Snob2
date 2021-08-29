#ifndef _YoungTableaux
#define _YoungTableaux

#include "CombinatorialBank.hpp"


namespace Snob2{

  class YoungTableaux{
  public:

    IntegerPartition p;
    const vector<YoungTableau*>* tableaux;
    bool is_view=false;

    ~YoungTableaux(){
      if(!is_view){
	for(auto p:*tableaux) delete p;
	delete tableaux;
      }
    }

  public:

    YoungTableaux(const IntegerPartition& _p): p(_p){
      tableaux=&_combibank->get_YoungTableaux(p);
      is_view=true;
    }


  public: // Access

    int size() const{
      return tableaux->size();
    }

    YoungTableau operator[](const int i){
      return *(*tableaux)[i];
    }

  };

}

#endif 
