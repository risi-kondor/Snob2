#include "Snob2_base.cpp"
#include "Snob2_session.hpp"
#include "SnClasses.hpp"


using namespace cnine;
using namespace Snob2;

//typedef CscalarObj cscalar;
//typedef CtensorObj ctensor;

int main(int argc, char** argv){
  Snob2_session session;

  SnOverSm Q(5,3);
  cout<<Q.get_order()<<endl;

  SnElement sigma=Q.identity(); 
  cout<<sigma<<endl;
  cout<<endl; 

  int N=Q.get_order();
  for(int i=0; i<N; i++){
    //cout<<sn.element(i)<<endl;
    cout<<Q.element(i)<<" "<<Q.index(Q.element(i))<<endl;
  }

}
