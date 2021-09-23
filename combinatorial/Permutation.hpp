#ifndef _Permutation
#define _Permutation

//#include "CyclicShifts.hpp"

#include "Snob2_base.hpp"

namespace Snob2{


  class Permutation{
  public:

  public:

    int n;
    int* p;


  public: // Constructors


    Permutation(const int _n, const cnine::fill_raw& dummy): 
      n(_n){
      p=new int[n];
    }

    Permutation(const int _n, const cnine::fill_identity& dummy): 
      n(_n){
      p=new int[n];
      for(int i=0; i<n; i++) p[i]=i+1;
    }

    Permutation(const initializer_list<int> list): 
      Permutation(list.size(), cnine::fill_raw()){
      int i=0; for(auto v:list) p[i++]=v;
      if(!check_valid()){cerr<<"Invalid permutation"<<endl;}
    }	

    Permutation(const vector<int> x): n(x.size()){
      p=new int[n]; 
      for(int i=0; i<n; i++) p[i]=x[i];
    }

    /*
      Permutation(const CyclicShifts& x): n(x.size()){
      p=new int[n]; for(int i=0; i<n; i++) p[i]=i+1;
      for(int i=0; i<n; i++){
      for(int j=0; j<i; j++) if (p[j]>=x[i]) p[j]++;
      p[i]=x[i];
      }
      }

      Permutation(const CyclicShifts& x, const int _n): n(_n){
      p=new int[n]; for(int i=0; i<n; i++) p[i]=i+1;
      for(int i=0; i<x.size(); i++){
      int ii=n-x.size()+i;
      for(int j=0; j<ii; j++) if (p[j]>=x[i]) p[j]++;
      p[ii]=x[i];
      }
      }
    */



    Permutation(const Permutation& x): n(x.n){
      p=new int[n]; 
      for(int i=0; i<n; i++) p[i]=x.p[i];
    }

    Permutation(Permutation&& x): n(x.n) {
      p=x.p; x.p = NULL;
    }
  
    Permutation operator=(const Permutation& x){
      n=x.n; delete[] p; p=new int[n]; 
      for(int i=0; i<n; i++) p[i]=x.p[i];
      return *this;
    }

    Permutation& operator=(Permutation&& x){
      if (this!=&x) {n=x.n; delete[] p; p=x.p; x.p = NULL;}
      return *this;
    }

    ~Permutation(){delete[] p;}


  public: // named constructors

    static Permutation Identity(const int _n){
      Permutation p(_n,cnine::fill_raw()); 
      for(int i=0; i<_n; i++) p.p[i]=i+1; 
      return p;
    }

    //static Permutation Random(const int n);

  
  public: // Access

    int getn() const{
      return n;
    }

    int size() const{
      return n;
    }

    int operator()(const int i) const{
      return p[i-1];
    }

    int operator[](const int i) const{
      return p[i];
    }

    int& operator[](const int i){
      return p[i];
    }

    bool operator==(const Permutation& x) const{
      if(n!=x.n) return false;
      for(int i=0; i<n; i++) if(p[i]!=x.p[i]) return false;
      return true;
    }

    Permutation operator!() const{
      Permutation result(n,cnine::fill_raw());
      for(int i=0; i<n; i++) result.p[p[i]-1]=i+1;
      return result;
    }


  public: 

    Permutation operator*(const Permutation& x) const{
      Permutation result(n,cnine::fill_raw());
      for(int i=0; i<n; i++) result.p[i]=p[x(i+1)-1];
      return result;
    }

    Permutation& operator*=(const Permutation& x){
      for(int i=0; i<n; i++) p[i]=x(p[i]);
      return *this;
    }

    Permutation inverse() const{
      Permutation r(n,cnine::fill_raw());
      for(int i=1; i<=n; i++)
	r.p[p[i-1]-1]=i;
      return r;
    }

    Permutation inv() const{
      return inverse();
    }

    bool check_valid() const{
      vector<bool> a(n,false);
      for(int i=0; i<n; i++){
	if(p[i]<1 || p[i]>n || a[p[i]-1]) return false;
	a[p[i]-1]=true;
      }
      return true;
    }


  public: 

    //Permutation& apply_inv_cyclic_shift(const int i, const int j){
    //p[j-1]
    //}


  public: // I/O 

    string str(const string indent="") const{
      ostringstream oss;
      oss<<"[ "; 
      for(int i=0; i<n; i++) oss<<p[i]<<" ";
      oss<<"]"; 
      return oss.str();
    }
     
    
    friend ostream& operator<<(ostream& stream, const Permutation& x){
      stream<<x.str(); return stream;
    }

  };

//ostream& operator<<(ostream& stream, const Permutation& sigma);
//LatexMath& operator<<(LatexMath& stream, const Permutation& sigma);

}


#endif
