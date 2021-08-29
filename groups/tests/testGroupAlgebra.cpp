#include "Snob2_base.cpp"
#include "Snob2_session.hpp"

#include "RtensorObj.hpp"
#include "GroupClasses.hpp"

using namespace cnine;
using namespace Snob2;

//typedef CscalarObj cscalar;
typedef RtensorObj rtensor;


int main(int argc, char** argv){
  Snob2_session session;
  cout<<endl;

  CyclicGroup G(5);
  Gdims dims({3});

  GroupAlgebra<CyclicGroup,rtensor> A(G,dims);
  cout<<A<<endl;

}

