#ifndef _ClausenFFT
#define _ClausenFFT

#include "ClausenFFTObj.hpp"
#include "SnFFTbank.hpp"
#include "SnFunction.hpp"


namespace Snob2{

  class ClausenFFT{
  public:

    ClausenFFTObj* obj;

    ClausenFFT(const int n){
      obj=_snfftbank->get_FFT(n);
    }

    ClausenFFT(const int n, const int m){
      obj=_snfftbank->get_FFT(n,m);
    }


  public:


    SnVec operator()(const SnFunction& f) const{
      return (*obj)(f);
    }

    SnVec operator()(const SnOverSmFunction& f){
      return (*obj)(f);
    }

    SnFunction inv(const SnVec& w){
      return obj->inv(w);
    }

    SnOverSmFunction inv_snsm(const SnVec& w){
      return obj->inv_snsm(w);
    }


  public: // ----- I/O ---------------------------------------------------------------------------------------


    string str(const string indent="") const{
      return obj->str();
    }

    friend ostream& operator<<(ostream& stream, const ClausenFFT& x){
      stream<<x.str(); return stream;
    }


  };

}

#endif


    //FunctionOnGroup<SnOverSmObj,rtensor> inv_snsm(const SnVec& w){
    //return obj->inv_snsm(w);
    //}

    //SnVec operator()(const FunctionOnGroup<SnOverSmObj,rtensor>& f){
    //return (*obj)(f);
    //}

