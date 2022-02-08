
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef _associative_container
#define _associative_container

#include "Snob2_base.hpp"
#include "GenericIterator.hpp"


namespace Snob2{


  template<typename KEY, typename OBJ>
  class associative_container_temporary{
  public:

    const KEY& _key;
    OBJ* _val;

    associative_container_temporary(const KEY& __key, OBJ* __val): _key(__key), _val(__val){}
      
  public:

    operator OBJ&(){
      return *_val;
    }

    OBJ& val(){
      return *_val;
    }

    const KEY& key(){
      return _key;
    }

  };

  
  template<typename KEY, typename OBJ>
  class associative_container_iterator{
  public:
    
    typedef typename map<KEY,OBJ*>::iterator _iterator;
    typedef associative_container_temporary<KEY,OBJ> temp;
    

    _iterator it;

    associative_container_iterator(const _iterator& _it):
      it(_it){}

    void operator++(){++it;}

    void  operator++(int a){++it;}

    //pair<KEY,const OBJ&> operator*() const{
    //return pair<KEY,const OBJ&>(it->first,*it->second);
    //}

    int dummy() const{}
      
    temp operator*() const{
      return temp(it->first,it->second); 
    }
      
    //const KEY& key() const{
    //return it->second;
    //}

    bool operator==(const associative_container_iterator& x) const{
      return it==x.it;
    }

    bool operator!=(const associative_container_iterator& x) const{
      return it!=x.it;
    }

  };



  template<typename KEY,typename OBJ>
  class associative_container{
  public:

    typedef associative_container_iterator<KEY,OBJ> iterator;

    //vector<OBJ*> v;
    mutable map<KEY,OBJ*> _map;
    
    ~associative_container(){
      for(auto p: _map) 
	delete p.second;
    }

    associative_container(){}


  public: // ---- Copying ------------------------------------------------------------------------------------
    

    associative_container(const associative_container& x){
      for(auto p: x._map)
	_map[p.first]=new OBJ(*p.second);
    }

    associative_container(associative_container&& x){
      _map=x._map;
      x._map.clear();
    }

    associative_container& operator=(const associative_container& x){
      clear();
      for(auto p: x._map)
	_map[p.first]=new OBJ(*p.second);
      return *this;
    }

    associative_container& operator=(associative_container&& x){
      clear();
      _map=x._map;
      x._map.clear();
      return *this;
    }


  public: // ---- Access -------------------------------------------------------------------------------------


    int size() const{
      return _map.size();
    }

    OBJ* pointer_to(const KEY& key) const{
      if(!exists(key)) insert(new OBJ());
      return _map[key];
    }

    OBJ& operator[](const KEY& key) const{
      if(!exists(key)) insert(new OBJ());
      return *_map[key];
    }

    void insert(const KEY& key, OBJ* obj){
      assert(!exists(key));
      _map[key]=obj;
    }

    void insert(const KEY& key, const OBJ& obj){
      assert(!exists(key));
      _map[key]=new OBJ(obj);
    }

    void insert(const KEY& key, OBJ&& obj){
      assert(!exists(key));
      _map[key]=new OBJ(std::move(obj)); 
    }

    bool exists(const KEY& key) const{
      return _map.find(key)!=_map.end();
    }

    iterator begin() const{
      return iterator(_map.begin());
    }

    iterator end() const{
      return iterator(_map.end());
    }

    void clear(){
      for(auto p: _map) 
	delete _map.second;
      _map.clear();
    }

  public: // ---- I/O -----------------------------------------------------------------------------------------


    string str(const string indent="") const{
      ostringstream oss;
      for(auto& p:_map){
	oss<<indent<<p.first.str()<<":"<<endl;
	oss<<p.second->str(indent+"  ")<<endl;
      }
      return oss.str();
    }

    friend ostream& operator<<(ostream& stream, const associative_container& x){
      stream<<x.str(); return stream;
    }

  };

}

#endif
