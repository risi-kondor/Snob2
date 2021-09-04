#include "Snob2_base.cpp"
#include "Snob2_session.hpp"
#include "CombinatorialClasses.hpp"
#include "SnClasses.hpp"
#include "SnMultiVec.hpp"

using namespace cnine;
using namespace Snob2;

//typedef CscalarObj cscalar;
//typedef CtensorObj ctensor;



int main(int argc, char** argv){

  Snob2_session session;
  CombinatorialClasses combi_classes;
  SnClasses Snclasses;
  cout<<endl;

  Sn G(4);
  FunctionOnGroup<Sn,cnine::RtensorObj> f(G,cnine::fill::gaussian);
  cout<<f<<endl;

  SnMultiVec fv(f);
  printl("fv",fv);
}

