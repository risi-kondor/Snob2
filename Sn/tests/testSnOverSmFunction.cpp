#include "Snob2_base.cpp"
#include "Snob2_session.hpp"
#include "SnClasses.hpp"
#include "FunctionOnGroup.hpp"
#include "RtensorObj.hpp"
#include "Gdims.hpp"
#include "SnOverSmFunction.hpp"

using namespace cnine;
using namespace Snob2;


int main(int argc, char** argv){
  Snob2_session session;

  Sn sn(4);
  SnOverSm X(4,3);
  SnOverSmFunction f(4,3,cnine::fill::gaussian);

  cout<<f<<endl;

  cout<<sn.element(3)<<endl;
  //cout<<f.left_translate(sn.element(3))<<endl;
  //cout<<f.right_translate(sn.element(3))<<endl;
}
