
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef _SnIrrep
#define _SnIrrep

#include "SnIrrepObj.hpp"
#include "SnBank.hpp"


namespace Snob2{

  //typedef cnine::RtensorObj rtensor;


  class SnIrrep{
  public:

    const SnIrrepObj* obj;
    IntegerPartition lambda;


  public:

    SnIrrep(){}

    SnIrrep(const SnIrrepObj* _obj):
      obj(_obj), lambda(_obj->lambda){}

    SnIrrep(const IntegerPartition& _lambda): lambda(_lambda){
      obj=_snbank->get_Sn(_lambda.getn())->get_irrep(_lambda);
    }

    SnIrrep(const initializer_list<int> list): lambda(list){
      obj=_snbank->get_Sn(lambda.getn())->get_irrep(lambda);
    }

    SnIrrep(const vector<int> list): lambda(list){
      obj=_snbank->get_Sn(lambda.getn())->get_irrep(lambda);
    }


  public: // Access

    int getn() const{
      return obj->n;
    }

    int getd() const{
      return obj->d;
    }

    int dim() const{
      return obj->d;
    }

    bool operator<(const SnIrrep& y) const{
      return (obj->lambda)<(y.obj->lambda);
    }


  public: 

    rtensor operator()(const SnElement& sigma) const{
      rtensor R(cnine::dims(obj->d,obj->d),cnine::fill::identity);
      obj->apply_left(R,sigma);
      return R;
    }

    rtensor operator()(const Transposition& x) const{
      rtensor R(cnine::dims(obj->d,obj->d),cnine::fill::identity);
      obj->apply_left(R,ContiguousCycle(x.i,x.j));
      obj->apply_left_inv(R,ContiguousCycle(x.i+1,x.j));
      return R;
    }

    rtensor transp(const int i, const int j) const{
      rtensor R(cnine::dims(obj->d,obj->d),cnine::fill::identity);
      obj->apply_left(R,ContiguousCycle(i,j));
      obj->apply_left_inv(R,ContiguousCycle(i+1,j));
      return R;
    }

    /*
    rtensor JucysMurphy(const int k){
      rtensor R(cnine::dims(obj->d,obj->d),cnine::fill::zero);
      rtensor A(cnine::dims(obj->d,obj->d),cnine::fill::identity);
      for(int i=k-1; i>=1; i--){
	obj->apply_left(A,i);
	rtensor B(A);
	obj->apply_left_inv(B,ContiguousCycle(i+1,k));
	R+=B;
      }
      return R;
    }
    */

    rtensor JucysMurphy(const int k){
      return obj->JucysMurphy(k);
    }


  public: // ---- In-place operations ------------------------------------------------------------------------


    void apply_transp(const cnine::Rtensor3_view& T, const int tau) const{
      obj->apply_transp(T,tau);
    }


    void apply(const cnine::Rtensor3_view& A, const ContiguousCycle& cyc) const{
      obj->apply(A,cyc);
    }

    void apply(const cnine::Rtensor3_view& A, const Transposition& x) const{
      obj->apply(A,x);
    }


  public:

    string str(const string indent="") const{
      return "SnIrrep("+lambda.str()+")";
    }

    friend ostream& operator<<(ostream& stream, const SnIrrep& x){
      stream<<x.str(); return stream;
    }

  };

}

#endif
