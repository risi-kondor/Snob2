#include "Snob2_base.cpp"
#include "Snob2_session.hpp"
#include "SnClasses.hpp"
#include "FunctionOnGroup.hpp"
#include "RtensorObj.hpp"
//#include "Gdims.hpp"
#include "SnVec.hpp" 
#include "CombinatorialClasses.hpp"
#include "ClausenFFTObj.hpp"

using namespace cnine;
using namespace Snob2;

//typedef CscalarObj cscalar;
//typedef CtensorObj ctensor;



int main(int argc, char** argv){
  Snob2_session session;
  SnClasses Snclasses;
  CombinatorialClasses combi_classes;
  cout<<endl;

  ClausenFFTObj FFT(4);
  cout<<FFT<<endl;

  Sn G(4);
  FunctionOnGroup<Sn,cnine::RtensorObj> f(G,cnine::fill::gaussian);
  cout<<f<<endl;

  SnVec v=FFT(f);
  printl("v",v);

}

