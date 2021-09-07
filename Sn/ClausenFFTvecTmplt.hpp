#ifndef _ClausenFFTvecTmplt
#define _ClausenFFTvecTmplt

#include "ClausenFFTpartTmplt.hpp"

namespace Snob2{

  class ClausenFFTvecTmplt{
  public:

    int n;
    vector<ClausenFFTpartTmplt*> parts;
    map<IntegerPartition,int> parts_map;


  public:

  public: // ---- Access -------------------------------------------------------------------------------------


    ClausenFFTpartTmplt* get_part(const IntegerPartition& lambda){
      if(parts_map.find(lambda)==parts_map.end()){
	int ix=parts.size(); 
	ClausenFFTpartTmplt* p=new ClausenFFTpartTmplt(lambda,ix);
	parts.push_back(p);
	parts_map[lambda]=ix;
	return p;
      }
      return parts[parts_map[lambda]];
    }


  public: // ---- Creating the transform ---------------------------------------------------------------------


    ClausenFFTvecTmplt(const int _n){
      assert(_n==1);
      n=1;
      auto seed=get_part(IntegerPartition({1}));
      seed->blocks.push_back(new ClausenFFTblockTmplt(0,0,0));
      seed->d=1;
      seed->m=1;
    }
    
    
    ClausenFFTvecTmplt(const ClausenFFTvecTmplt& prev){
      n=prev.n+1;

      for(int i=0; i<prev.parts.size(); i++){
	ClausenFFTpartTmplt& part=*prev.parts[i];
	IntegerPartition lambda=part.irrep->lambda;
	int k=lambda.k;
	int m=part.m;
	for(int i=0; i<k; i++)
	  if(i==0||lambda.p[i]<lambda.p[i-1]){
	    lambda.p[i]++;
	    get_part(lambda)->add(part);
	    lambda.p[i]--;
	  }
	lambda.add(k);
	get_part(lambda)->add(part);
      }
    }


  public: // ---- Applying the transform ---------------------------------------------------------------------


    SnVecPack* pack(const FunctionOnGroup<Sn,rtensor>& f){
      SnVecPack* R=new SnVecPack();
      int N=f.size();
      R->vecs.resize(N);
      SnIrrepObj* irrep=_snbank->get_irrep(IntegerPartition({1}));
      for(int i=0; i<N; i++)
	R->vecs[i]=new SnVec(new SnPart(irrep,f(i)));
      return R;
    }


    SnVecPack* uptransform(const SnVecPack* V) const{
      int N=V->vecs.size();
      int newN=N/n;
      SnVecPack* W=new SnVecPack();
      W->vecs.resize(newN);

      for(int c=0; c<newN; c++){

	SnVec* w=new SnVec();
	for(int i=0; i<parts.size(); i++)
	  w->parts.push_back(new SnPart(parts[i]->irrep,parts[i]->m,cnine::fill::zero));
  
	for(int i=0; i<n; i++){
	  SnVec u=uptransform(*V->vecs[c*n+i]);
	  u.apply_inplace(ContiguousCycle(n-i,n));
	  (*w).add(u);
	}

	W->vecs[c]=w;
      }

      return W;
    }


    SnVec uptransform(const SnVec& v) const{
      SnVec w;
      for(auto p:parts){
	w.parts.push_back(new SnPart(p->uptransform(v)));
      }
      return w;
    }


  public:

    string str(const string indent="") const{
      ostringstream oss;
      oss<<indent<<"Level "<<n<<":"<<endl;
      for(int i=0; i<parts.size(); i++){
	//cout<<indent<<"Part "<<i<<" ("<< parts[i]->irrep->lambda<<":"<<endl;
	oss<<parts[i]->str(indent+"  ");
      }
      return oss.str();
    }

    friend ostream& operator<<(ostream& stream, const ClausenFFTvecTmplt& x){
      stream<<x.str(); return stream;
    }

  };

}

#endif
