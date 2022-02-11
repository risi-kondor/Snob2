// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2022, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#include "Snob2_base.cpp"
#include "Snob2_session.hpp"
#include "CombinatorialClasses.hpp"
#include "SnClasses.hpp"
#include "SnPart.hpp"
#include "SnProductRepresentation.hpp"
#include "associative_container.hpp"

using namespace cnine;
using namespace Snob2;

//typedef CscalarObj cscalar;
typedef RtensorObj rtensor;



int main(int argc, char** argv){

  Snob2_session session;

  int n=5; // (3,2) (2,2)+(3,1)
  int k=5;
  IntegerPartition lamb({n-2,2});
  SnIrrep rho(lamb);

  rtensor A=rho(Transposition(1,k));
  for(int i=2; i<=k-1; i++)
    A+=rho(Transposition(i,k));
  cout<<A.str("",0.0001)<<endl;
  cout<<rho.JucysMurphy(k).str("",0.0001)<<endl;

  auto rho2=rho*rho;
  rtensor B=rho2.JucysMurphy(k);
  cout<<B.str("",0.0001)<<endl;

  /*
  SnIrrep rho3({3,1});
  rtensor A3=rho3(Transposition(1,4));
  for(int i=2; i<=3; i++)
    A3+=rho3(Transposition(i,4));
  cout<<A3<<endl;
  */

}

  /*

  rtensor D=rho(SnElement::transposition(n,n-1,n));
  rtensor E=rho(SnElement::transposition(n,1,2));
  rtensor R=rho(SnElement::contiguous_cycle(n,1,n));
  rtensor L=rho(SnElement::contiguous_cycle(n,n,1));
  rtensor F=L*L*E*R*R;

  cout<<D<<endl;
  cout<<E<<endl;
  cout<<F.str("",0.001)<<endl;
  */

  


