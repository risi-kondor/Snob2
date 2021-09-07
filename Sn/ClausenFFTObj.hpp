#ifndef _ClausenFFTObj
#define _ClausenFFTObj

#include "SnVecPack.hpp"
#include "ClausenFFTvecTmplt.hpp"


namespace Snob2{

  typedef cnine::RtensorObj rtensor;


  class ClausenFFTObj{
  public:

    vector<ClausenFFTvecTmplt*> levels;

  public:

    ClausenFFTObj(const int n){
      levels.resize(n);
      levels[0]=new ClausenFFTvecTmplt(1);
      for(int l=2; l<=n; l++)
	levels[l-1]=new ClausenFFTvecTmplt(1,*levels[l-2]);
    }


  public: // ---- Applying transform -------------------------------------------------------------------------


    SnVec operator()(const FunctionOnGroup<Sn,rtensor>& f){
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


    FunctionOnGroup<Sn,rtensor> inv(const SnVec& v){
      int n=levels.size();
      auto& final_parts=levels[n-1]->parts;
      assert(v.parts.size()==final_parts.size());
      for(int i=0; i<v.parts.size(); i++){
	assert(v.parts[i]->dim(0)==final_parts[i]->d);
	assert(v.parts[i]->dim(1)==final_parts[i]->m);
      }
      
      SnVecPack* prev_v=levels[n-1]->pack(v);
      SnVecPack* v=nullptr;
      for(int l=n-1; l>0; l--){
	v=levels[l-1]->downtransform(prev_v);
	delete prev_v;
	prev_v=v;
      }

      Sn G(n);
      FunctionOnGroup<Sn,rtensor> R(G,cnine::fill::zero);
      return R;
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

}

#endif
