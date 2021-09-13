#ifndef _SnFFTbank
#define _SnFFTbank

#include "ClausenFFTObj.hpp"


namespace Snob2{

  class SnFFTbank{
  public:

    unordered_map<ClausenFFTobjSignature,ClausenFFTObj*> ffts;

    ~SnFFTbank(){
      for(auto& p:ffts) 
	delete p.second;
    }


  public:

    ClausenFFTObj* get_FFT(const int n, const int m=-1){
      ClausenFFTobjSignature s(n,m);
      auto it=ffts.find(s);
      if(it!=ffts.end()) return it->second;
      ClausenFFTObj* t;
      if(m>-1) t=new ClausenFFTObj(n,m);
      else t=new ClausenFFTObj(n);
      ffts[s]=t;
      return t;
    }

  };

}

#endif
