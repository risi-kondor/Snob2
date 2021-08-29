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

  //ProductGroup<CyclicGroup,CyclicGroup> G(G1,G2);
  auto G=G1*G2;

  cout<<G.identity()<<endl<<endl;

  for(int i=0; i<G.size(); i++) 
    cout<<G.element(i)<<endl;

}

