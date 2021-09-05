#include "Snob2_base.cpp"
#include "Snob2_session.hpp"
#include "CombinatorialClasses.hpp"
#include "SnClasses.hpp"
#include "SnRepresentation.hpp"

using namespace cnine;
using namespace Snob2;


int main(int argc, char** argv){

  Snob2_session session;
  CombinatorialClasses combi_classes;
  SnClasses Snclasses;
  cout<<endl;

  SnRepresentation mu;
  mu.set(SnIrrep({4,2}),1);
  mu.set(SnIrrep({5,1}),2);

  cout<<mu<<endl;


  Sn G(5);
  cout<<G.repr()<<endl;

}
