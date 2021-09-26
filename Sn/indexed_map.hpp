#ifndef _indexed_map
#define _indexed_map

#include "Snob2_base.hpp"
#include "GenericIterator.hpp"


namespace Snob2{

  template<typename KEY,typename OBJ>
  class indexed_map{
  public:

    class iterator: public GenericIterator<indexed_map,OBJ*>{
    public:
      using Snob2::GenericIterator<indexed_map,OBJ*>::GenericIterator;
    };


    vector<OBJ*> v;
    mutable map<KEY,OBJ*> map;
    
    ~indexed_map(){
      for(auto p:v) 
	delete p;
    }


  public: // ---- Copying ------------------------------------------------------------------------------------


    indexed_map& operator=(indexed_map&& x){
      v=x.v;
      x.v.clear();
      map=x.map;
      x.map.clear();
    }


  public: // ---- Access -------------------------------------------------------------------------------------

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

    iterator begin() const{
      return iterator(this);
    }

    iterator end() const{
      return iterator(this,size());
    }

    void clear(){
      v.clear();
      map.clear();
    }

    void wipe(){
      for(auto p:v) 
	delete p;
      v.clear();
      map.clear();
    }

  };


  template<typename KEY,typename OBJ>
  class indexed_mapB{
  public:

    class iterator: public GenericIterator<indexed_mapB,OBJ*>{
    public:
      using Snob2::GenericIterator<indexed_mapB,OBJ*>::GenericIterator;
    };


    vector<OBJ*> v;
    mutable map<KEY,OBJ*> map;
    
    ~indexed_mapB(){
      for(auto p:v) 
	delete p;
    }

  public: // ---- Copying ------------------------------------------------------------------------------------


    indexed_mapB& operator=(const indexed_mapB& x){
      v=x.v;
      map=x.map;
      return *this;
    }

    indexed_mapB& operator=(indexed_mapB&& x){
      v=x.v;
      x.v.clear();
      map=x.map;
      x.map.clear();
      return *this;
    }


  public: // ---- Access -------------------------------------------------------------------------------------


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

    void push_back(OBJ* obj){
      v.push_back(obj);
      map[obj->key()]=obj;
    }

    bool exists(const KEY& key) const{
      return map.find(key)!=map.end();
    }

    iterator begin() const{
      return iterator(this);
    }

    iterator end() const{
      return iterator(this,size());
    }

    void clear(){
      v.clear();
      map.clear();
    }

    void wipe(){
      for(auto p:v) 
	delete p;
      v.clear();
      map.clear();
    }

  };

}

#endif
