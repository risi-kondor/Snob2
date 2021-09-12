#include "Snob2_base.cpp"
#include "Snob2_session.hpp"

using namespace cnine;
using namespace Snob2;


int main(int argc, char** argv){
  Snob2_session session;

  IntegerPartition lambda({4,3,1});
  YoungTableau t(lambda);
  cout<<t<<endl;

  StandardYoungTableaux T(IntegerPartition({2,2,1}));
  for(int i=0; i<T.size(); i++) 
    cout<<T[i]<<endl;

}

