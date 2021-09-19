#ifndef _SnType
#define _SnType

#include "IntegerPartition.hpp"

namespace Snob2{

  class SnType{
  public:

    mutable map<IntegerPartition,int> map;
    

  public:

    SnType(){}

    SnType(const IntegerPartition& lambda, const int n){
      map[lambda]=n;
    }

    SnType(const initializer_list<tuple<IntegerPartition,int>> list){
      for(auto p: list) map[std::get<0>(p)]=std::get<1>(p);
    }


  public: // ---- Access ------------------------------------------------------------------------------------


    void set(const IntegerPartition& lambda, const int m){
      map[lambda]=m;
    }

    void add(const IntegerPartition& lambda, const int m){
      if(map.find(lambda)==map.end()) map[lambda]=m;
      else map[lambda]=map[lambda]+m;
    }


  public:


    bool operator==(const SnType& x) const{
      return map==x.map;
    }

    bool operator<(const SnType& x) const{
      return map<x.map;
    }


  public:  // ---- Operations -------------------------------------------------------------------------------


    SnType static down(const IntegerPartition& lambda){
      SnType tau;
      lambda.foreach_sub([&](const IntegerPartition& mu){
	  tau.map[mu]++;
	});
      return tau;
    }

    SnType static cat(const vector<SnType*>& v){
      SnType tau;
      for(auto q:v)
	for(auto& p:q->map)
	  tau.add(p.first,p.second);
      return tau;
   }


  public: // ---- I/O ---------------------------------------------------------------------------------------


    string str(const string indent="") const{
      ostringstream oss;
      int i=0; 
      oss<<"(";
      for(auto& p:map){
	oss<<""<<p.first.str()<<":"<<p.second<<"";
	if(++i<map.size()) oss<<",";
      }
      oss<<")";
      return oss.str();
    }

    friend ostream& operator<<(ostream& stream, const SnType& x){
      stream<<x.str(); return stream;
    }


  };

}

#endif
