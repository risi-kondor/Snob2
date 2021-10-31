#ifndef _StandardYoungTableaux
#define _StandardYoungTableaux

#include "CombinatorialBank.hpp"


namespace Snob2{

  class StandardYoungTableaux{
  public:

    class iterator: public GenericIterator<StandardYoungTableaux,YoungTableau>{
    public:
      using GenericIterator::GenericIterator;
    };


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

    YoungTableau operator[](const int i) const{
      return *(*tableaux)[i];
    }

    iterator begin() const{
      return iterator(this);
    }

    iterator end() const{
      return iterator(this,size());
    }


  public: // I/O

    string str(const string indent="") const{
      return indent+"StandardYoungTableaux"+p.str();
    }

    friend ostream& operator<<(ostream& stream, const StandardYoungTableaux& x){
      stream<<x.str(); return stream;
    }

    

  };

}

#endif 
