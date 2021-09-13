#include "Snob2_base.cpp"
#include "Snob2_session.hpp"
#include "SnOverSmFunction.hpp"
#include "ClausenFFT.hpp"

using namespace cnine;
using namespace Snob2;


int main(int argc, char** argv){
  Snob2_session session;

  int n=5;
  int m=3;


  ClausenFFT FFT(n,m);
  cout<<FFT<<endl;

  SnOverSmFunction f=SnOverSmFunction::gaussian(5,3);
  cout<<f<<endl;

  SnVec v=FFT(f);
  printl("v",v);

  auto fd=FFT.inv_snsm(v);
  printl("fd",fd);

}

