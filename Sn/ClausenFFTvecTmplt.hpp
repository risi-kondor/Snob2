#ifndef _ClausenFFTvecTmplt
#define _ClausenFFTvecTmplt

#include "ClausenFFTpartTmplt.hpp"
#include "SnFunction.hpp"
#include "FunctionOnGroup.hpp"

namespace Snob2{

  class ClausenFFTvecTmplt{
  public:

    int n;
    ClausenFFTvecTmplt* next=nullptr;

    vector<ClausenFFTpartTmplt*> parts;
    map<IntegerPartition,int> parts_map;


  public: // ---- Constructors -------------------------------------------------------------------------------


    ClausenFFTvecTmplt(const ClausenFFTvecTmplt& x)=delete;
    ClausenFFTvecTmplt& operator=(const ClausenFFTvecTmplt& x)=delete;


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


    void add(ClausenFFTpartTmplt* part){
      const IntegerPartition& lambda=part->irrep->lambda;
      if(parts_map.find(lambda)!=parts_map.end()){cerr<<"Part already present"<<endl; exit(1);}
      int ix=parts.size(); 
      parts.push_back(part);
      parts_map[lambda]=ix;
    }


  public: // ---- Creating the transform ---------------------------------------------------------------------


    ClausenFFTvecTmplt(const int _n): n(_n){
      auto seed=get_part(IntegerPartition({n}));
      seed->blocks.push_back(new ClausenFFTblockTmplt(0,0,0));
      seed->d=1;
      seed->m=1;
    }
    
    
    ClausenFFTvecTmplt(int s, const ClausenFFTvecTmplt& prev){ // s is a dummy here
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
      const_cast<ClausenFFTvecTmplt&>(prev).next=this;
    }


  public: // ---- Applying the transform ---------------------------------------------------------------------


    // Deprecated
    /*
    SnVecPack* pack(const FunctionOnGroup<Sn,rtensor>& f){
      SnVecPack* R=new SnVecPack();
      int N=f.size();
      R->vecs.resize(N);
      SnIrrepObj* irrep=_snbank->get_irrep(IntegerPartition({1}));
      for(int i=0; i<N; i++)
	R->vecs[i]=new SnVec(new SnPart(irrep,f(i)));
      return R;
    }
    */

    SnVecPack* pack(const FunctionOnGroup<SnOverSmObj,rtensor>& f){
      SnVecPack* R=new SnVecPack();
      int N=f.size();
      R->vecs.resize(N);
      SnIrrepObj* irrep=_snbank->get_irrep(IntegerPartition({1}));
      for(int i=0; i<N; i++)
	R->vecs[i]=new SnVec(new SnPart(irrep,f(i)));
      return R;
    }

    SnVecPack* pack(const SnFunction& f){
      SnVecPack* R=new SnVecPack();
      int N=f.size();
      R->vecs.resize(N);
      SnIrrepObj* irrep=_snbank->get_irrep(IntegerPartition({1}));
      for(int i=0; i<N; i++)
	R->vecs[i]=new SnVec(new SnPart(irrep,f(i)));
      return R;
    }

    SnVecPack* pack(const SnVec& v){
      SnVecPack* R=new SnVecPack();
      /*
      SnVec* w=new SnVec();
      for(auto p: v.parts){
	rtensor M(p->dims,cnine::fill::zero,p->dev);
	M.add(*p,p->irrep->d);
	w->parts.push_back(new SnPart(p->irrep,M));
      }
      */
      R->vecs.push_back(new SnVec(v));
      return R;
    }

    // Deprecated
    /*
    FunctionOnGroup<Sn,rtensor> unpack(SnVecPack* V){
      int N=V->vecs.size();
      Sn G(n);
      FunctionOnGroup<Sn,rtensor> R(G,cnine::fill::ones);
      assert(R.size()==N);
      for(int i=0; i<N; i++)
	R.set_value(i,V->vecs[i]->parts[0]->get_value(0,0));
      return R;
    }
    */

    SnFunction unpack(SnVecPack* V){
      int N=V->vecs.size();
      SnFunction R(n,cnine::fill::ones);
      assert(R.size()==N);
      for(int i=0; i<N; i++)
	R.set_value(i,V->vecs[i]->parts[0]->get_value(0,0));
      return R;
    }

    FunctionOnGroup<SnOverSmObj,rtensor> unpack(int m, SnVecPack* V){
      int N=V->vecs.size();
      FunctionOnGroup<SnOverSmObj,rtensor> R(_snbank->get_SnOverSm(n,m),cnine::fill::ones);
      assert(R.size()==N);
      for(int i=0; i<N; i++)
	R.set_value(i,V->vecs[i]->parts[0]->get_value(0,0));
      return R;
    }

    SnVecPack* uptransform(const SnVecPack* V) const{
      int N=V->vecs.size();
      int newN=N/n;
      SnVecPack* W=new SnVecPack();
      W->vecs.resize(newN);

      for(int c=0; c<newN; c++){
	//cout<<"----------- c="<<c<<endl;
	    
	SnVec* w=new SnVec();
	for(int i=0; i<parts.size(); i++){
	  //cout<<*parts[i]->irrep<<endl;
	  w->parts.push_back(new SnPart(parts[i]->irrep,parts[i]->m,cnine::fill::zero,0));
	}
  
	for(int i=0; i<n; i++){
	  //cout<<"----- i="<<i<<endl;
	  SnVec u=uptransform(*V->vecs[c*n+i]);
	  u.apply_inplace(ContiguousCycle(n-i,n));
	  //cout<<"*"<<u<<endl;
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


    SnVecPack* downtransform(const SnVecPack* V) const{
      int N=V->vecs.size();
      int newN=N*(n+1);
      SnVecPack* W=new SnVecPack();
      W->vecs.resize(newN);

      for(int c=0; c<N; c++){
	//cout<<"c="<<c<<endl;

	for(int i=0; i<n+1; i++){
	  //cout<<"i="<<i<<endl;

	  /*
	  SnVec* w=new SnVec();
	  for(int j=0; j<parts.size(); j++){
	    w->parts.push_back(new SnPart(parts[j]->irrep,parts[j]->m,cnine::fill::zero,0));
	  }
	  */

	  SnVec u(*V->vecs[c]);
	  u.apply_inplace_inv(ContiguousCycle(n+1-i,n+1));
	  //SnVec ud=downtransform(u);
	  //(*w).add(ud);

	  W->vecs[c*(n+1)+i]=new SnVec(downtransform(u));

	}
      }

      return W;
    }


    SnVec downtransform(const SnVec& v) const{

      SnVec w;
      for(int i=0; i<parts.size(); i++){
	w.parts.push_back(new SnPart(parts[i]->irrep,parts[i]->m,cnine::fill::zero,0));
      }

      assert(next);
      int i=0; 
      for(auto p:next->parts){
	const SnPart& part=*v.parts[i];
	for(auto q:p->blocks){
	  float c=((float)part.irrep->d)/(w.parts[q->subix]->irrep->d*(n+1));
	  part.add_block_to(q->ioffs,q->joffs,*w.parts[q->subix],c);
	}
	i++;
      }

      return w;
    }


  public:

    string str(const string indent="") const{
      ostringstream oss;
      oss<<indent<<"Level "<<n<<":"<<endl;
      for(int i=0; i<parts.size(); i++){
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
