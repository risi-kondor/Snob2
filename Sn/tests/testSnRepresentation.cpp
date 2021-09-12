#include "Snob2_base.cpp"
#include "Snob2_session.hpp"
#include "CombinatorialClasses.hpp"
#include "SnClasses.hpp"
#include "SnRepresentation.hpp"

using namespace cnine;
using namespace Snob2;


int main(int argc, char** argv){

  Snob2_session session;
  //CombinatorialClasses combi_classes;
  //SnClasses Snclasses;

  SnType tau({{{4,2},1},{{3,3},4}});
  SnRepresentation mu(tau);
  cout<<mu<<endl;

  cout<<mu.induced()<<endl;




  Sn G(5);
  //cout<<G.repr()<<endl;

}
