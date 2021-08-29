#include "Snob2_base.cpp"
#include "Snob2_session.hpp"
#include "GroupClasses.hpp"

using namespace cnine;
using namespace Snob2;


int main(int argc, char** argv){
  Snob2_session session;
  cout<<endl;

  DihedralGroup G(5);

  for(int i=0; i<G.size(); i++) cout<<G.element(i)<<endl;
  cout<<endl;

  cout<<G.s()*G.r(2)*G.s()<<endl;

}

