#ifndef _SnType
#define _SnType

#include "IntegerPartition.hpp"

namespace Snob2{

  class SnType{
  public:

    unordered_map<IntegerPartition,int> map;
    

  public:

    SnType(){}

    SnType(const IntegerPartition& lambda, const int n){
      map[lambda]=n;
    }


  public:

    void set(const IntegerPartition& lambda, const int n){
      map[lambda]=n;
    }


  public:

    string str(const string indent="") const{
      ostringstream oss;
      for(auto& p:map)
	oss<<"( "<<p.first.str()<<" , "<<p.second<<" )"<<endl;
      return oss.str();
    }

    friend ostream& operator<<(ostream& stream, const SnType& x){
      stream<<x.str(); return stream;
    }


  };

}

#endif
