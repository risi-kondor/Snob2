#include "Snob2_base.cpp"
#include "Snob2_session.hpp"
#include "SnClasses.hpp"
#include "FunctionOnGroup.hpp"
#include "RtensorObj.hpp"
#include "Gdims.hpp"
#include "SnFunction.hpp"

using namespace cnine;
using namespace Snob2;

//typedef CscalarObj cscalar;
//typedef CtensorObj ctensor;



int main(int argc, char** argv){
  Snob2_session session;

  int n=4;
  Sn sn(n);
  SnFunction f(n,cnine::fill::gaussian);

  cout<<f<<endl;

  cout<<sn.element(3)<<endl;
  cout<<f.left_translate(sn.element(3))<<endl;
  cout<<f.right_translate(sn.element(3))<<endl;
}
