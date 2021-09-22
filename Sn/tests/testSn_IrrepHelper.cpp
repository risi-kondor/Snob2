#include "Snob2_base.cpp"
#include "Snob2_session.hpp"
#include "CombinatorialClasses.hpp"
#include "SnClasses.hpp"
#include "SnPart.hpp"

#include "Sn_IrrepHelper.hpp"

using namespace cnine;
using namespace Snob2;

//typedef CscalarObj cscalar;
//typedef CtensorObj ctensor;



int main(int argc, char** argv){

  Snob2_session session;

  Sn G(5);

  cout<<G.irreps.size()<<endl<<endl;

  cout<<G.irreps[2]<<endl;
  cout<<G.irreps[IntegerPartition({4,1})]<<endl;
  cout<<endl;

  //for(auto it=G.irreps.begin(); it!=G.irreps.end(); it++)
  //cout<<*it<<endl;

  for(auto p:G.irreps) 
    cout<<p<<endl;

}
