#include "GElib_base.cpp"
#include "GElibSession.hpp"
#include "SnClasses.hpp"


using namespace cnine;
using namespace GElib;

//typedef CscalarObj cscalar;
//typedef CtensorObj ctensor;



int main(int argc, char** argv){
  GElibSession session;
  SnClasses Snclasses;
  cout<<endl;

  IntegerPartition lambda({4,3,1});

  cout<<lambda<<endl;

  IntegerPartitions IP(5);
  for(int i=0; i<IP.size(); i++)
    cout<<IP[i]<<endl;


}

