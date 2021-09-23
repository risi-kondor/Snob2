#include "Snob2_base.cpp"
#include "Snob2_session.hpp"

using namespace cnine;
using namespace Snob2;


int main(int argc, char** argv){
  Snob2_session session;

  IntegerPartition lambda({4,3,1});
  cout<<lambda<<endl<<endl;

  IntegerPartitions IP(5);
  for(int i=0; i<IP.size(); i++)
    cout<<IP[i]<<endl;

  for(auto p:IP)
    cout<<p<<endl;

}

