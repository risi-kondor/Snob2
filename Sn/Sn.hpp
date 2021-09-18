#ifndef _Sn
#define _Sn

#include "SnBank.hpp"
#include "SnElement.hpp"
#include "SnIrrep.hpp"
//#include "SnModule.hpp"
//#include "SnRepresentation.hpp"
#include "SnCharBank.hpp"


namespace Snob2{

  class Sn{
  public:

    const int n;
    SnObj* obj;

    Sn(const int _n): n(_n){
      obj=_snbank->get_Sn(n);
    }

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


  public: // Elements
   
    SnElement identity() const{
      return SnElement(n,cnine::fill_identity());
    }

    SnElement element(const int i) const{
      return obj->element(i);
    }

    int index(const SnElement& sigma) const{
      return obj->index(sigma);
    }


  public: // Classes

    int ncclasses() const{
      return obj->ncclasses(); 
    }

    IntegerPartition cclass(const int i) const{
      return obj->cclass(i);
    }

    int index(const IntegerPartition& lambda) const{
      return obj->index(lambda);
    }


  public: // Representations

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


  public: // Characters 


    SnClassFunction character(const IntegerPartition& lambda) const{
      return SnClassFunction(*_sncharbank->get_character(lambda));
    }


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

