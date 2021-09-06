#ifndef _SnObj
#define _SnObj

#include "Snob2_base.hpp"
#include <map>

#include "IntegerPartitions.hpp"

#include "SnElement.hpp"
#include "SnIrrepObj.hpp"
#include "SnModule.hpp"
//#include "SnRepresentation.hpp"


namespace Snob2{

  class SnObj{
  public:

    friend class Sn;

    const int n;
    int order;

    SnObj* Snminus1=nullptr;

    vector<SnIrrepObj*> irreps;
    map<IntegerPartition,SnIrrepObj*> irrep_map;
    SnModule module;
    //SnRepresentation repr;
    bool all_irreps=false;


  public:


    SnObj(const int _n): n(_n){
      order=factorial(n);
      //cout<<"Creating Sn("<<n<<")"<<endl;
    }

    ~SnObj(){
      for(auto p:irreps) delete p;
    }


  public:

    SnElement element(int e) const{
      SnElement p(n,cnine::fill_identity());

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


  public:

    /*
    SnIrrep irrep(const IntegerPartition& lambda){
      SNOB2_ASSERT(lambda.getn()==n,"Irrep index of Sn must be a partition of n.");
      return SnIrrep(get_irrep(lambda));
    }
    */

    SnIrrepObj* get_irrep(const IntegerPartition& lambda){
      auto it=irrep_map.find(lambda);
      if(it!=irrep_map.end()) return it->second;
      SnIrrepObj* irrep=new SnIrrepObj(lambda);
      irreps.push_back(irrep);
      irrep_map[lambda]=irrep;
      return irrep;
    }

    vector<SnIrrepObj*> get_all_irreps(){
      make_all_irreps();
      return irreps;
    }

    void make_ancestors(SnIrrepObj& irrep){
      if(irrep.ancestors.size()>0) return;
      assert(Snminus1);
      IntegerPartition lamb(irrep.lambda);
      for(int i=0; i<lamb.k-1; i++){
	if(lamb.p[i+1]==lamb.p[i]) continue;
	lamb.p[i]--;
	irrep.ancestors.push_back(Snminus1->get_irrep(lamb));
	lamb.p[i]++;
      }
      lamb.p[lamb.k-1]--;
      if(lamb.p[lamb.k-1]==0) lamb.k--;
      if(lamb.k>0)
	irrep.ancestors.push_back(Snminus1->get_irrep(lamb));
    }


    SnModule get_module(){
      make_all_irreps();
      return module;
    }


  private:

    void make_all_irreps(){
      if(all_irreps) return;
      IntegerPartitions partitions=IntegerPartitions(n);
      for(int i=0; i<partitions.size(); i++){
	get_irrep(partitions[i]);
      }
      for(auto p:irreps)
	module.set(p->lambda,p->d);
      //for(auto p:irreps)
      //repr.set(p->lambda,p->d);
      all_irreps=true;
    }

  };




}

#endif
