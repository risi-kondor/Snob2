#include "Snob2_base.cpp"
#include "Snob2_session.hpp"
#include "SnClasses.hpp"
#include "FunctionOnGroup.hpp"
#include "RtensorObj.hpp"
//#include "Gdims.hpp"
#include "SnVec.hpp" 
#include "CombinatorialClasses.hpp"
//#include "ClausenFFTObj.hpp"
#include "ClausenFFT.hpp"
#include "SnFunction.hpp"

using namespace cnine;
using namespace Snob2;

//typedef CscalarObj cscalar;
//typedef CtensorObj ctensor;



int main(int argc, char** argv){
  Snob2_session session;

  int n=4;

  //ClausenFFTObj FFT(n);
  //cout<<FFT<<endl;

  ClausenFFT FFT(n); 

  SnFunction f(n,cnine::fill::gaussian);
  cout<<f<<endl;

  SnVec v=FFT(f);
  printl("v",v);

  auto fd=FFT.inv(v);
  printl("fd",fd);

}

