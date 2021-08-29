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

  DihedralGroup G(5);
  DihedralGroupElement g=G.element(2);
  FunctionOnGroup<DihedralGroup,ctensor> f(G,cnine::fill::gaussian);
  cout<<f<<endl;

  auto F=Fourier(f);
  cout<<F<<endl;

  auto fd=iFourier(F);
  cout<<fd<<endl;

  /*
  auto F2=F.left(g);
  auto f2d=iFourier(F2);
  cout<<f2d<<endl;

  auto F3=F.inv();
  auto f3d=iFourier(F3);
  cout<<f3d<<endl;
  */

}

