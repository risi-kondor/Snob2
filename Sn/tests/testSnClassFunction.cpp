#include "Snob2_base.cpp"
#include "Snob2_session.hpp"

#include "SnClassFunction.hpp"

using namespace cnine;
using namespace Snob2;

//typedef CscalarObj cscalar;
//typedef CtensorObj ctensor;



int main(int argc, char** argv){
  Snob2_session session;

  Sn G(4);
  SnClassFunction f(4,cnine::fill::gaussian);

  cout<<f<<endl;

  //cout<<f[{2,2}]<<endl;
}
