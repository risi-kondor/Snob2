#include "Snob2_base.cpp"
#include "Snob2_session.hpp"
#include "CombinatorialClasses.hpp"
#include "SnClasses.hpp"
#include "SnType.hpp"

using namespace cnine;
using namespace Snob2;

//typedef CscalarObj cscalar;
//typedef CtensorObj ctensor;



int main(int argc, char** argv){

  Snob2_session session;

  SnType type0(IntegerPartition({4,2}),1);
  type0.set(IntegerPartition({5,1}),2);
  cout<<type0<<endl;

  SnType type1({{{4,2},1},{{3,3},4}});
  cout<<type1<<endl;


}
