#ifndef _StandardYoungTableaux
#define _StandardYoungTableaux

#include "CombinatorialBank.hpp"


namespace Snob2{

  class StandardYoungTableaux{
  public:

    IntegerPartition p;
    const vector<YoungTableau*>* tableaux;
    bool is_view=false;

    ~StandardYoungTableaux(){
      if(!is_view){
	for(auto p:*tableaux) delete p;
	delete tableaux;
      }
    }

  public:

    StandardYoungTableaux(const IntegerPartition& _p): p(_p){
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
