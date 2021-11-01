
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef _SnVec
#define _SnVec

#include "SnPart.hpp"
#include "SnType.hpp"
//#include "SnMultiVec.hpp"
//#include "SnModule.hpp"
#include "SnRepresentation.hpp"

namespace Snob2{

  class SnVec{
  public:

    indexed_mapB<IntegerPartition,SnPart> parts;

    ~SnVec(){}


  public: // ---- Constructors --------------------------------------------------------------------------------


    SnVec(){}

    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnVec(const SnType& _type, const FILLTYPE& fill, const int _dev=0){
      for(auto& p:_type._map)
	parts.insert(p.first,new SnPart(p.first,p.second,fill,_dev));
    }

    
    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnVec(const SnRepresentation& M, const FILLTYPE& fill, const int _dev=0):
      SnVec(M.obj,fill,_dev){}


    SnVec(const SnType& _type, const int _dev=0):
      SnVec(_type,cnine::fill_raw(),_dev){}


    SnVec(SnPart* part){
      parts.insert(part->get_lambda(),part);
      //parts.push_back(part);
    }


  public: // ---- Named constructors -------------------------------------------------------------------------


    static SnVec raw(const SnType& _type, const int _dev=0){
      return SnVec(_type,cnine::fill::raw,_dev);
    }

    static SnVec zero(const SnType& _type, const int _dev=0){
      return SnVec(_type,cnine::fill::zero,_dev);
    }

    static SnVec identity(const SnType& _type, const int _dev=0){
      return SnVec(_type,cnine::fill::identity,_dev);
    }

    static SnVec gaussian(const SnType& _type, const int _dev=0){
      return SnVec(_type,cnine::fill::gaussian,_dev);
    }


  public: // ---- Copying ------------------------------------------------------------------------------------


    SnVec(const SnVec& x){
      //cout<<" copy vec"<<endl;
      parts=x.parts;
    }
    
    SnVec(SnVec&& x){
      //cout<<" move vec"<<endl;
      parts=std::move(x.parts);
    }

    SnVec& operator=(const SnVec& x){
      parts=x.parts;
      return *this;
    }

    SnVec& operator=(SnVec&& x){
      parts=std::move(x.parts);
      return *this;
    }


  public: // ---- Access -------------------------------------------------------------------------------------


    int getn() const{
      assert(parts.size()>0);
      return parts[0]->getn();
    }
    
    int index(const IntegerPartition& lambda) const{
      for(int i=0; i<parts.size(); i++)
	if(parts[i]->irrep->lambda==lambda) return i;
      return -1;
    }


  public: // ---- Operations ---------------------------------------------------------------------------------


    SnVec apply(const SnElement& sigma) const{
      SnVec R;
      for(auto p: parts){
	SnPart* A=new SnPart(*p);
	A->apply_inplace(sigma);
	R.parts.insert(p->get_lambda(),A);
      }
      return R;
    }

    SnVec& apply_inplace(const SnElement& sigma){
      for(auto p:parts)
	p->apply_inplace(sigma);
      return *this;
    }

    SnVec& apply_inplace(const ContiguousCycle& cyc){
      for(auto p:parts)
	p->apply_inplace(cyc);
      return *this;
    }

    SnVec& apply_inplace_inv(const ContiguousCycle& cyc){
      for(auto p:parts)
	p->apply_inplace_inv(cyc);
      return *this;
    }

    

  public: // ---- Cumulative operations ----------------------------------------------------------------------


    void add(const SnVec& y){
      assert(parts.size()==y.parts.size());
      for(int i=0; i<parts.size(); i++)
	parts[i]->add(*y.parts[i]);
    }


  public: // ---- Operations ---------------------------------------------------------------------------------


    //SnVec down() const{ // TODO 
    //SNOB2_UNIMPL();
    //return *this;
    //}

    SnVec static down(const SnPart& v){
      SnVec R;
      int offs=0;
      v.get_lambda().foreach_sub([&](const IntegerPartition& lambda){
	  auto P=new SnPart(lambda,1,cnine::fill::zero);
	  v.add_block_to(offs,0,*P);
	  R.parts.insert(lambda,P);
	  offs+=P->getd();
	});
      //cout<<R<<endl;
      return R;
    }

    SnVec static up(const SnType& tau, const SnVec& v){
      SnVec R(tau,cnine::fill_zero());
      vector<int> offs(v.parts.size(),0);
      //cout<<tau<<endl;
      for(auto& p:tau._map){
	SnPart& dest=*R.parts[R.index(p.first)];
	int m=dest.dims(1);
	int voffs=0;
	p.first.foreach_sub([&](const IntegerPartition& mu){
	    int ix=v.index(mu);
	    assert(ix>=0);
	    dest.add_to_block_block(voffs,0,*v.parts[ix],0,offs[ix],v.parts[ix]->dims(0),m);
	    voffs+=v.parts[ix]->dims(0);
	    offs[ix]+=m;
	  });
      }
      return R;
    }

    SnVec static cat(const vector<SnVec>& v){
      SnType tau;
      for(int i=0; i<v.size(); i++)
	for(auto p: v[i].parts)
	  tau.add(p->get_lambda(),p->getm());
      SnVec R(tau,cnine::fill::zero);
      vector<int> offs(R.parts.size(),0);
      for(int i=0; i<v.size(); i++)
	for(auto p: v[i].parts){
	  int ix=R.index(p->irrep->lambda);
	  R.parts[ix]->add_to_block(0,offs[ix],*p);
	  offs[ix]+=p->dims(1);
	}
      return R;
    }

    /*
    SnVec operator*(const float c) const{
      SnVec v;
      for(auto p: parts)
	v.parts.push_back(new SnPart((*p)*c));
      return v;
    }
    */

    //SnType CGtype(const IntegerPartition& x, IntegerPartition& y){}


  public: // ---- Fourier transforms ------------------


    /*
    static SnVec Fourier(const FunctionOnGroup<Sn,rtensor>& f){
      const int n=f.G.getn();
      vector<SnMultiVec*> levels(n);
      cout<<0<<endl;
      levels[0]=new SnMultiVec(f);
      for(int l=1; l<n; l++){
	cout<<l<<endl;
	levels[l]=new SnMultiVec(levels[l-1]->uptransform());
	delete levels[l-1];
      }
      return SnVec(std::move(*levels[n-1]));
    }

    SnVec(const SnMultiVec& x){
      assert(x.N==1);
      for(auto p:x.parts)
	parts.push_back(new SnPart(*p.second));
    }

    SnVec(SnMultiVec&& x){
      assert(x.N==1);
      for(auto p:x.parts)
	parts.push_back(new SnPart(p.second->irrep,std::move(*p.second)));
      //parts.push_back(p->convert_to_part_destrictively());
    }
    */

    /*
    SnVec induce() const{
      SnRepresentationObj* induced_rep=repr->get_induced();
      SnVec v(induced_rep,cnine::fill::zero);

      int iso_ix=0;
      for(auto& p:induced_rep.isotypics){
	const SnIsotypicObj& iso=p.second;
	SnPart& part=*v.parts[iso_ix];

	int ioffs=0;
	int joffs=0;
	for(auto subp:iso.subs){
	  const SnPart& sub
	  const int I=
	  for(int i=0; i<
	}

	iso_ix++;
      }
      return v;
    }
    */

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


  inline SnVec operator*(const SnElement& sigma, const SnVec& v){
    return v.apply(sigma);
  }

}

#endif
    /*
    template<typename FILLTYPE>
    SnVec(const SnModule& M, const FILLTYPE& fill, const int _dev=0){
      for(auto& p:M.map)
	parts.push_back(new SnPart(p.first,p.second,fill,_dev));
      //parts.push_back(new SnPart(p.first,p.second,fill,_dev));
    }
    */
    //template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    //SnVec(const Sn& G,const FILLTYPE& fill, const int _dev=0){
    //IntegerPartitions Lambda(
    //}


    /*
    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnVec(const SnRepresentationObj* _repr, const FILLTYPE& fill, const int _dev=0)//: repr(_repr)
    {
      for(auto& p:_repr->isotypics){
	const SnIsotypicObj& iso=p.second;
	parts.push_back(new SnPart(iso.irrep,iso.m,fill,_dev));
      }
    }
    */

