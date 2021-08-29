#ifndef _SnObj
#define _SnObj

#include "Snob2_base.hpp"

#include "SnElement.hpp"


namespace Snob2{

  class SnObj{
  public:

    const int n;
    int order;

    SnObj* Snminus1=nullptr;

    SnObj(const int _n): n(_n){
      order=factorial(n);
      cout<<"Creating Sn("<<n<<")"<<endl;
    }


  public:

    SnElement element(int e) const{
      SnElement p(n,cnine::fill_identity());
      vector<int> r(n);
      for(int i=0; i<n; i++) r[i]=i+1;

      vector<int> s(n);
      for(int i=n; i>0; i--){
	s[i-1]=i-e/factorial(i-1);
	e=e%factorial(i-1);
      }

      for(int i=2; i<=n; i++){
	int t=s[i-1];
	for(int k=i; k>=t+1; k--) 
	  p[k-1]=p[k-2];
	p[t-1]=i;
      }

      return p;
    }

    int index(const SnElement& sigma) const{
      if(n==1) return 0;
      assert(sigma.size()==n);
      SnElement tau(n-1,cnine::fill::raw);
      int a=0;
      int i=0;
      for(; i<n; i++){
	if(sigma[i]==n){a=n-i-1; break;}
	else tau[i]=sigma[i];
      }
      i++;
      for(;i<n;i++) tau[i-1]=sigma[i];
      //cout<<" "<<a<<" "<<tau<<endl;
      return Snminus1->index(tau)+a*factorial(n-1);
    }

  };

}

#endif
