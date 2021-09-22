#ifndef _indexed_map
#define _indexed_map

#include "Snob2_base.hpp"

namespace Snob2{

  template<typename KEY,typename OBJ>
  class indexed_map{
  public:

    vector<OBJ*> v;
    mutable map<KEY,OBJ*> map;
    
    ~indexed_map(){
      for(auto p:v) 
	delete p;
    }

  public:

    int size() const{
      return v.size();
    }

    OBJ* operator[](const int i) const{
      return v[i];
    }

    OBJ* operator[](const KEY& key) const{
      return map[key];
    }

    void insert(const KEY& key, OBJ* obj){
      v.push_back(obj);
      map[key]=obj;
    }

    bool exists(const KEY& key) const{
      return map.find(key)!=map.end();
    }


  };

}

#endif
