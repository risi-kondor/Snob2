#ifndef _SnRepresentation
#define _SnRepresentation

#include <map>

#include "IntegerPartition.hpp"
#include "SnIrrep.hpp"

namespace Snob2{

  class SnRepresentation{
  public:

    //map<IntegerPartition,int> map;
    map<SnIrrep,int> irreps;
    

  public:

    SnRepresentation(){}

    SnRepresentation(const SnIrrep& rho, const int n){
      irreps[rho]=n;
    }

    SnRepresentation(const IntegerPartition& lambda, const int n){
      irreps[SnIrrep(lambda)]=n; //_snbank->get_irrep(lambda);
    }


  public:

    void set(const SnIrrep& rho, const int n){
      irreps[rho]=n;
    }


  public:

    string str(const string indent="") const{
      ostringstream oss;
      oss<<"SnRepresentation(";
      int i=0; 
      for(auto& p:irreps){
	oss<<"("<<p.first.lambda.str()<<":"<<p.second<<")";
	if(++i<irreps.size()) oss<<",";
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
