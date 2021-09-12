#include "Snob2_base.cpp"
#include "Snob2_session.hpp"
#include "CombinatorialClasses.hpp"
#include "SnClasses.hpp"
#include "SnPart.hpp"


using namespace cnine;
using namespace Snob2;

//typedef CscalarObj cscalar;
//typedef CtensorObj ctensor;



int main(int argc, char** argv){

  Snob2_session session;

  int n=4;
  Sn G(n);
  IntegerPartition lambda({n-1,1});
  SnIrrep rho(lambda); 
  SnElement sigma({1,2,4,3}); 

  SnPart A=SnPart::identity(rho,3);
  cout<<A<<endl;

  SnPart B=SnPart::identity(lambda,3);
  cout<<B<<endl;

  SnPart C=B.apply(sigma);
  printl("C",C);

}
