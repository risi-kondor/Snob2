#ifndef _SnRepresentation
#define _SnRepresentation

#include <map>

//#include "IntegerPartition.hpp"
//#include "SnIrrep.hpp"
//#include "SnType.hpp"
#include "SnBank.hpp"
#include "SnRepresentationBank.hpp"
#include "SnRepresentationObj.hpp"


namespace Snob2{

  class SnRepresentation{
  public:

    SnRepresentationObj* obj;


  public:

    SnRepresentation(){}

    SnRepresentation(SnRepresentationObj* _obj): obj(_obj){};

    SnRepresentation(const SnType& _type){
      obj=_snrepbank->get_rep(_type);
    }


  public: // ---- Access -----------------------------------------------------------------------------------

    
    //int n_isotypics

    SnRepresentation induced(){
      return SnRepresentation(obj->get_induced());
    }

    SnRepresentation restricted(){
      return SnRepresentation(obj->get_restricted());
    }


  public:

    string str(const string indent="") const{
      ostringstream oss;
      oss<<"SnRep(";
      int i=0; 
      for(auto& p:obj->isotypics){
	oss<<p.second;
	if(++i<obj->isotypics.size()) oss<<",";
      }
      oss<<")"<<endl;
      return oss.str();
    }

    friend ostream& operator<<(ostream& stream, const SnRepresentation& x){
      stream<<x.str(); return stream;
    }


  };

}

#endif
