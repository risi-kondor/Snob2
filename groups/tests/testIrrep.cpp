#include "Snob2_base.cpp"
#include "Snob2_session.hpp"

#include "RtensorObj.hpp"
#include "CtensorObj.hpp"
#include "GroupClasses.hpp"

using namespace cnine;
using namespace Snob2;

//typedef CscalarObj cscalar;
typedef RtensorObj rtensor;
typedef CtensorObj ctensor;


int main(int argc, char** argv){
  Snob2_session session;
  cout<<endl;

  CyclicGroup G(5);
  CyclicGroupIrrep rho=G.irrep(2);
  CyclicGroupElement g=G.element(2);

  cout<<rho(g)<<endl<<endl;

}

