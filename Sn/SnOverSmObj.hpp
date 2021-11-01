
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef _SnOverSmObj
#define _SnOverSmObj

#include "SnBank.hpp"
#include "SnElement.hpp"


namespace Snob2{


  class SnOverSmObj{
  public:

    const int n;
    const int m;
    //SnObj* obj;

    SnOverSmObj(const int _n, const int _m): n(_n), m(_m){
      //obj=_snbank->get_Sn(n);
    }

    static SnElement dummy_element(){return SnElement::Identity(1);}


  public: // ---- Access ------------------------------------------------------------------------------------


    int size() const{
      return factorial(n)/factorial(m);
    }

    int order() const{
      return size();
    }

    int get_order() const{
      return size();
    }

    SnElement identity() const{
      return SnElement(n,cnine::fill_identity());
    }

    SnElement element(int e) const{
      SnElement p(n,cnine::fill_identity());

      e*=factorial(m);
      vector<int> s(n);
      for(int i=n; i>m; i--){
	s[i-1]=i-e/factorial(i-1);
	e=e%factorial(i-1);
      }

      for(int i=m+1; i<=n; i++){
	int t=s[i-1];
	for(int k=i; k>=t+1; k--) 
	  p[k-1]=p[k-2];
	p[t-1]=i;
      }

      return p;
    }

    int index(const SnElement& sigma) const{
      assert(sigma.size()==n);
      int t=0; 
      vector<int> s(n);
      for(int i=0; i<n; i++) s[i]=sigma[i];

      for(int _n=n; _n>m; _n--){
	int a=0;
	int i=0;
	for(; i<_n; i++){
	  if(s[i]==_n){t+=(_n-i-1)*factorial(_n-1); break;}
	  //else tau[i]=sigma[i];
	}
	i++;
	for(;i<_n;i++) s[i-1]=s[i];
      }
      return t/factorial(m);
    }

  };


}

#endif 
