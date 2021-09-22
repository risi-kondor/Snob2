#ifndef _ClausenFFTObj
#define _ClausenFFTObj

#include "SnVecPack.hpp"
#include "ClausenFFTvecTmplt.hpp"
#include "SnFunction.hpp"


namespace Snob2{

  typedef cnine::RtensorObj rtensor;


  class ClausenFFTObj{
  public:

    int n;
    int m=-1;

    vector<ClausenFFTvecTmplt*> levels;

  public:

    ClausenFFTObj(const int _n): n(_n){
      levels.resize(n);
      levels[0]=new ClausenFFTvecTmplt(1);
      for(int l=2; l<=n; l++)
	levels[l-1]=new ClausenFFTvecTmplt(1,*levels[l-2]);
    }

    ClausenFFTObj(const int _n, const int _m): n(_n), m(_m){
      levels.resize(n-m+1);
      levels[0]=new ClausenFFTvecTmplt(m);
      for(int l=m+1; l<=n; l++)
	levels[l-m]=new ClausenFFTvecTmplt(1,*levels[l-m-1]);
    }


  public: // ---- Applying transform -------------------------------------------------------------------------


    SnVec operator()(const FunctionOnGroup<SnOverSmObj,rtensor>& f){
      int n=levels.size();

      SnVecPack* prev_v=levels[0]->pack(f);
      SnVecPack* v=nullptr;
      for(int l=2; l<=n; l++){
	//cout<<"level" <<l<<endl;
	v=levels[l-1]->uptransform(prev_v);
	delete prev_v;
	prev_v=v;
      }

      SnVec R(std::move(*v->vecs[0]));
      delete v;
      return R;
    }


    SnVec operator()(const SnFunction& f){
      int n=levels.size();

      SnVecPack* prev_v=levels[0]->pack(f);
      SnVecPack* v=nullptr;
      for(int l=2; l<=n; l++){
	//cout<<"level" <<l<<endl;
	v=levels[l-1]->uptransform(prev_v);
	delete prev_v;
	prev_v=v;
      }

      SnVec R(std::move(*v->vecs[0]));
      delete v;
      return R;
    }


    SnFunction inv(const SnVec& w){
      int n=levels.size();
      auto& final_parts=levels[n-1]->parts;
      assert(w.parts.size()==final_parts.size());
      for(int i=0; i<w.parts.size(); i++){
	assert(w.parts[i]->dim(0)==final_parts[i]->d);
	assert(w.parts[i]->dim(1)==final_parts[i]->m);
      }
      
      SnVecPack* prev_v=levels[n-1]->pack(w);
      SnVecPack* v=nullptr;
      for(int l=n-1; l>0; l--){
	//cout<<"l="<<l<<endl;
	v=levels[l-1]->downtransform(prev_v);
	delete prev_v;
	prev_v=v;
      }

      return levels[n-1]->unpack(v);
    }


    FunctionOnGroup<SnOverSmObj,rtensor> inv_snsm(const SnVec& w){
      //int n=levels.size();

      auto& final_parts=levels[n-m]->parts;
      assert(w.parts.size()==final_parts.size());
      for(int i=0; i<w.parts.size(); i++){
	cout<<*w.parts[i]<<endl;
	cout<<*final_parts[i]<<endl;
	assert(w.parts[i]->dim(0)==final_parts[i]->d);
	assert(w.parts[i]->dim(1)==final_parts[i]->m);
      }
      
      SnVecPack* prev_v=levels[n-m]->pack(w);
      SnVecPack* v=nullptr;
      for(int l=n-1; l>=m; l--){
	//cout<<"l="<<l<<endl;
	v=levels[l-m]->downtransform(prev_v);
	delete prev_v;
	prev_v=v;
      }

      return levels[n-m]->unpack(m,v);
    }


  public: // ----- I/O ---------------------------------------------------------------------------------------

    string str(const string indent="") const{
      ostringstream oss;
      oss<<"Clausen FFT:"<<endl;
      for(int i=0; i<levels.size(); i++){
	oss<<levels[i]->str("  ");
      }
      return oss.str();
    }

    friend ostream& operator<<(ostream& stream, const ClausenFFTObj& x){
      stream<<x.str(); return stream;
    }

  };


  class ClausenFFTobjSignature{
  public:

    int n,m;

    ClausenFFTobjSignature(const int _n, const int _m): n(_n), m(_m){}
    
    bool operator==(const ClausenFFTobjSignature& y) const{
      if(n!=y.n) return false;
      if(m!=y.m) return false;
      return true;
    }
  };

}

namespace std{
  template<>
  struct hash<Snob2::ClausenFFTobjSignature>{
  public:
    size_t operator()(const Snob2::ClausenFFTobjSignature& x) const{
      size_t r=1;
      r=(hash<int>()(x.n)<<1)^hash<int>()(x.m);
      return r;
    }
  };
}



#endif


    // Deprecated 
    /*
    FunctionOnGroup<Sn,rtensor> inv(const SnVec& w){
      int n=levels.size();
      auto& final_parts=levels[n-1]->parts;
      assert(w.parts.size()==final_parts.size());
      for(int i=0; i<w.parts.size(); i++){
	assert(w.parts[i]->dim(0)==final_parts[i]->d);
	assert(w.parts[i]->dim(1)==final_parts[i]->m);
      }
      
      SnVecPack* prev_v=levels[n-1]->pack(w);
      SnVecPack* v=nullptr;
      for(int l=n-1; l>0; l--){
	//cout<<"l="<<l<<endl;
	v=levels[l-1]->downtransform(prev_v);
	delete prev_v;
	prev_v=v;
      }

      return levels[n-1]->unpack(v);
    }
    */
 

    /*
    SnVec operator()(const FunctionOnGroup<Sn,rtensor>& f){ // Deprecated
      int n=levels.size();

      SnVecPack* prev_v=levels[0]->pack(f);
      SnVecPack* v=nullptr;
      for(int l=2; l<=n; l++){
	//cout<<"level" <<l<<endl;
	v=levels[l-1]->uptransform(prev_v);
	delete prev_v;
	prev_v=v;
      }

      SnVec R(std::move(*v->vecs[0]));
      delete v;
      return R;
    }
    */
