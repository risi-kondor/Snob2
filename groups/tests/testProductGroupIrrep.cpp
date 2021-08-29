#include "Snob2_base.cpp"
#include "Snob2_session.hpp"
#include "GroupClasses.hpp"

using namespace cnine;
using namespace Snob2;


int main(int argc, char** argv){
  Snob2_session session;
  cout<<endl;

  CyclicGroup G1(3);
  CyclicGroup G2(4);

  auto G=G1*G2;
  auto rho=G.irrep(3);

  for(int i=0; i<G.size(); i++) 
    cout<<rho(i)<<endl;

}

