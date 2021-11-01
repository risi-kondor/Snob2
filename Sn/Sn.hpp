
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef _Sn
#define _Sn

#include "SnBank.hpp"
#include "SnElement.hpp"
#include "SnCClass.hpp"
#include "SnIrrep.hpp"
//#include "SnModule.hpp"
//#include "SnRepresentation.hpp"
#include "SnCharBank.hpp"

#include "Sn_ElementHelper.hpp"
#include "Sn_CclassHelper.hpp"
#include "Sn_IrrepHelper.hpp"
#include "Sn_CharacterHelper.hpp"

namespace Snob2{

  class Sn{
  public:

    const int n;
    const SnObj* obj;

    Sn_ElementHelper elements;
    Sn_CClassHelper cclasses;
    Sn_IrrepHelper irreps;
    Sn_CharacterHelper characters;

  public:

    Sn(const SnObj* _obj): 
      n(_obj->n),
      obj(_obj),
      elements(_obj),
      cclasses(_obj),
      irreps(_obj),
      characters(_obj){}

    Sn(const int _n): 
      Sn(_snbank->get_Sn(_n)){}

    static SnElement dummy_element(){return SnElement::Identity(1);}
    static SnIrrep dummy_irrep(){return SnIrrep({1});}


  public: // Access

    int getn() const{
      return n;
    }

    int size() const{
      return obj->order;
    }

    int get_order() const{
      return obj->order;
    }


  public: // ---- Elements -----------------------------------------------------------------------------------

   
    SnElement identity() const{
      return SnElement(n,cnine::fill_identity());
    }

    SnElement element(const int i) const{
      return obj->element(i);
    }

    int index(const SnElement& sigma) const{
      return obj->index(sigma);
    }

    SnElement random() const{
      return obj->random();
    }


  public: // ---- Conjugacy classes --------------------------------------------------------------------------


    int ncclasses() const{
      return obj->ncclasses(); 
    }

    SnCClass cclass(const int i) const{
      return obj->cclass(i);
    }

    SnCClass cclass(const IntegerPartition& lambda) const{
      return obj->cclass(obj->index(lambda));
    }

    int index(const IntegerPartition& lambda) const{
      return obj->index(lambda);
    }

    int index(const SnCClass& lambda) const{
      return obj->index(lambda);
    }

    int class_size(const SnCClass& cc) const{
      return class_size(static_cast<const IntegerPartition&>(cc));
    }

    int class_size(const IntegerPartition& lambda) const{
      if(lambda.k==0) return 0;
      int prev=lambda.p[0];
      int count=1;
      int t=1;
      for(int i=1; i<lambda.k; i++){
	if(lambda.p[i]==prev) count++;
	else{
	  t*=pow(prev,count)*factorial(count);
	  prev=lambda.p[i];
	  count=1;
	}
      }
      t*=pow(prev,count)*factorial(count);
      return factorial(getn())/t;
    }

    int class_size(const int i) const{
      return class_size(cclass(i));
    }


  public: // ---- Representations ----------------------------------------------------------------------------


    SnIrrep irrep(const IntegerPartition& lambda) const{
      return SnIrrep(obj->get_irrep(lambda));
    }

    vector<SnIrrep> all_irreps() const{
      vector<SnIrrepObj*> objs=obj->get_all_irreps();
      vector<SnIrrep> R(objs.size());
      for(int i=0; i<objs.size(); i++)
	R[i]=SnIrrep(objs[i]);
      return R;
    }

    

  public: // ---- Characters ---------------------------------------------------------------------------------


    int nchars() const{
      return 0;
    }
    
    SnClassFunction character(const int i) const{
      return SnClassFunction(*_sncharbank->get_character({n}));
    }


    SnClassFunction character(const IntegerPartition& lambda) const{
      return SnClassFunction(*_sncharbank->get_character(lambda));
    }

    void make_all_chars(){}


  public:

    string str(const string indent="") const{
      return "Sn("+to_string(n)+")";
    }

    friend ostream& operator<<(ostream& stream, const Sn& x){
      stream<<x.str(); return stream;
    }


  };

}

#endif 
    /*
    SnModule module() const{
      return obj->get_module();
    }
    */
    
    //SnModule rep() const{
    //return obj->get_rep();
    //}

    /*
    SnRepresentation repr() const{
      obj->make_all_irreps();
      SnRepresentation R;
      for(auto p:obj->irreps){
	//cout<<p->lambda<<endl;
	R.set(p->lambda,p->d);
      }
      return R;
    }
    */

