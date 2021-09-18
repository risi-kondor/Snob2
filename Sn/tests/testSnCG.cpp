#include "Snob2_base.cpp"
#include "Snob2_session.hpp"
#include "CombinatorialClasses.hpp"
#include "SnClasses.hpp"
#include "SnPart.hpp"

#include "SnCGbank.hpp"
#include "SnCGcoefficient.hpp"
//class SnCGbank
//SnCGbank* _sncgbank=nullptr;

#include "SnPartProduct.hpp"


using namespace cnine;
using namespace Snob2;

//typedef CscalarObj cscalar;
//typedef CtensorObj ctensor;



int main(int argc, char** argv){

  Snob2_session session;

  int n=4;
  IntegerPartition lambda({n-1,1});

  cout<<SnCGcoefficient(lambda,lambda,{n-2,2})<<endl;;

  SnPart A=SnPart::gaussian(lambda,1);
  cout<<A<<endl;

  SnPart B=SnPart::gaussian(lambda,3);
  cout<<B<<endl;

  SnVec C=SnPartProduct(A,B);
  cout<<C<<endl;

}
