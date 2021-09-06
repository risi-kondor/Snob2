#ifndef _SnModule
#define _SnModule

#include <map>

#include "IntegerPartition.hpp"

namespace Snob2{

  class SnModule{
  public:

    map<IntegerPartition,int> map;
    

  public:

    SnModule(){}

    SnModule(const IntegerPartition& lambda, const int n){
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

    friend ostream& operator<<(ostream& stream, const SnModule& x){
      stream<<x.str(); return stream;
    }


  };

}

#endif
