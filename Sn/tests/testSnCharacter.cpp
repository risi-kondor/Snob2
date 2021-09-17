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

  Sn sn(4);

  for(int i=0; i<sn.ncclasses(); i++)
    cout<<sn.cclass(i)<<endl;

}
