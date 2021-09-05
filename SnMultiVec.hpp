#ifndef _SnVec
#define _SnVec

#include "SnPart.hpp"
#include "SnType.hpp"

namespace Snob2{

  class SnVec{
  public:

    vector<SnPart*> parts;
    //map<IntegerPartition,SnPart*> parts;

    ~SnVec(){
      for(auto p:parts) delete p;
    }

  public:

    SnVec(){}

    template<typename FILLTYPE>
    SnVec(const SnType& _type, const FILLTYPE& fill, const int _dev=0){
      for(auto& p:_type.map)
	parts.push_back(new SnPart(p.first,p.second,fill,_dev));
      //parts.push_back(new SnPart(p.first,p.second,fill,_dev));
    }


  public:

    static SnVec zero(const SnType& _type, const int _dev=0){
      return SnVec(_type,cnine::fill::zero,_dev);
    }

    static SnVec identity(const SnType& _type, const int _dev=0){
      return SnVec(_type,cnine::fill::identity,_dev);
    }

    static SnVec gaussian(const SnType& _type, const int _dev=0){
      return SnVec(_type,cnine::fill::gaussian,_dev);
    }


  public:

    SnVec apply(const SnElement& sigma) const{
      SnVec R;
      for(auto p: parts){
	SnPart* A=new SnPart(*p);
	A->apply_inplace(sigma);
	R.parts.push_back(A);
      }
      return R;
    }

    SnVec& apply_inplace(const SnElement& sigma){
      for(auto p:parts)
	p->apply_inplace(sigma);
      return *this;
    }


  public:

    string str(string indent="") const{
      ostringstream oss;
      for(auto p:parts){
	oss<<*p<<endl;
      }
      return oss.str();
    }

    friend ostream& operator<<(ostream& stream, const SnVec& x){
      stream<<x.str(); return stream;
    }

  };

}

#endif
