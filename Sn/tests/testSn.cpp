#include "Snob2_base.cpp"
#include "Snob2_session.hpp"
#include "CombinatorialClasses.hpp"
#include "SnClasses.hpp"


using namespace cnine;
using namespace Snob2;

//typedef CscalarObj cscalar;
//typedef CtensorObj ctensor;



int main(int argc, char** argv){

  Snob2_session session;
  CombinatorialClasses combi_classes;
  SnClasses Snclasses;
  cout<<endl;

  Sn G(4);
  cout<<G.get_order()<<endl;

  SnElement sigma=G.identity(); 
  cout<<sigma<<endl;
  cout<<endl; 

  int N=G.get_order();
  for(int i=0; i<N; i++){
    //cout<<sn.element(i)<<endl;
    cout<<G.element(i)<<" "<<G.index(G.element(i))<<endl;
  }

  SnModule M=G.module();
  cout<<M<<endl;

}


  //auto irreps=G.all_irreps();
  //for(auto p:irreps) cout<<p<<" "<<p.dim()<<endl;

