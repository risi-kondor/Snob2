
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
  class associative_container_iterator{
  public:
    
    typedef typename map<KEY,OBJ*>::iterator _iterator;

    _iterator it;

    associative_container_iterator(const _iterator& _it):
      it(_it){}

    void operator++(){++it;}

    void  operator++(int a){++it;}

    pair<KEY,const OBJ&> operator*() const{
      return pair<KEY,const OBJ&>(it->first,*it->second);
    }
      
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

    /*
    class iterator: public GenericIterator<associative_container,OBJ*>{
    public:
      using Snob2::GenericIterator<associative_containerB,OBJ*>::GenericIterator;
    };
    */

    vector<OBJ*> v;
    mutable map<KEY,OBJ*> _map;
    
    ~associative_container(){
      for(auto p:v) 
      delete p;
    }

    associative_container(){}


  public: // ---- Copying ------------------------------------------------------------------------------------
    

    associative_container(const associative_container& x){
      for(auto p:x){
	insert(p.first,p.second);
      }
      //for(auto p:x.v){
      //insert(new OBJ(*p)); // TODO 
      //}
    }

    associative_container(associative_container&& x){
      v=x.v;
      _map=x._map;
      x.v.clear();
      x._map.clear();
    }

    associative_container& operator=(const associative_container& x){
      clear();
      for(auto p:x){
	insert(p.first,p.second);
      }
      return *this;
    }

    associative_container& operator=(associative_container&& x){
      clear();
      v=x.v;
      _map=x._map;
      x.v.clear();
      x._map.clear();
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
      if(!exists(key)) insert(new OBJ());
      return _map[key];
    }

    void insert(const KEY& key, OBJ* obj){
      assert(!exists(key));
      v.push_back(obj);
      _map[key]=obj;
    }

    void insert(const KEY& key, const OBJ& obj){
      assert(!exists(key));
      OBJ* t=new OBJ(obj); 
      v.push_back(t);
      _map[key]=t;
    }

    void insert(const KEY& key, OBJ&& obj){
      assert(!exists(key));
      OBJ* t=new OBJ(std::move(obj)); 
      v.push_back(t);
      _map[key]=t;
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
      for(auto p:v) 
	delete p;
      v.clear();
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
