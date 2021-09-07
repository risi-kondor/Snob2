#include "Snob2_base.cpp"
#include "Snob2_session.hpp"
#include "CombinatorialClasses.hpp"
#include "SnClasses.hpp"
#include "RtensorObj_funs.hpp"

using namespace cnine;
using namespace Snob2;

//typedef CscalarObj cscalar;
//typedef CtensorObj ctensor;



int main(int argc, char** argv){

  Snob2_session session;
  CombinatorialClasses combi_classes;
  SnClasses Snclasses;
  cout<<endl;

  int n=4;
  IntegerPartition lambda({n-1,1});
  SnIrrep rho(lambda); 
  cout<<endl;

  SnElement sigma1({1,2,4,3});
  SnElement sigma2({1,3,2,4});
  SnElement sigma3({2,1,3,4});
  SnElement sigma4=sigma1*sigma2;
  SnElement sigma5=sigma3*sigma1*sigma2;

  auto R1=rho(sigma1);
  print("s1",sigma1);
  printl("rho(s1)",R1);

  auto R2=rho(sigma2);
  print("s2",sigma2);
  printl("rho(s2)",R2);

  auto R3=rho(sigma3);
  print("s3",sigma3);
  printl("rho(s3)",R3);

  auto R4=rho(sigma4);
  print("s4",sigma3);
  printl("rho(s4)",R4);

  auto R5=rho(sigma5);
  print("s5",sigma5);
  printl("rho(s5)",R5);

  auto R4d=(R1*R2);//*R2;
  cout<<endl;
  cout<<R4d<<endl;

  auto R5d=R1*R2;
  cout<<R5d<<endl;


}
