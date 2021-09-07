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
	levels[l-1]=new ClausenFFTvecTmplt(*levels[l-2]);
    }


  public:

    SnVec operator()(const FunctionOnGroup<Sn,rtensor>& f){
      int n=levels.size();

      SnVecPack* prev_v=levels[0]->pack(f);
      SnVecPack* v=nullptr;
      for(int l=2; l<=n; l++){
	v=levels[l-1]->uptransform(prev_v);
	delete prev_v;
	prev_v=v;
      }

      SnVec R(std::move(*v->vecs[0]));
      delete v;
      return R;
    }


  public:

    string str(const string indent="") const{
      ostringstream oss;
      oss<<"Clausen FFT:"<<endl;
      for(int i=0; i<levels.size(); i++){
	//oss<<"Level "<<i+1<<":"<<endl;
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
