#include "Snob2_base.cpp"
#include "Snob2_session.hpp"
#include "CombinatorialClasses.hpp"


using namespace cnine;
using namespace Snob2;

//typedef CscalarObj cscalar;
//typedef CtensorObj ctensor;



int main(int argc, char** argv){
  Snob2_session session;
  CombinatorialClasses combi_classes;
  cout<<endl;

  IntegerPartition lambda({4,3,1});
  YoungTableau t(lambda);
  cout<<t<<endl;

  YoungTableaux T(IntegerPartition({2,2,1}));
  for(int i=0; i<T.size(); i++) 
    cout<<T[i]<<endl;

}

