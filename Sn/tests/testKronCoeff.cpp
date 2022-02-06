
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.


#include "Snob2_base.cpp"
#include "Snob2_session.hpp"
#include "CombinatorialClasses.hpp"
#include "SnClasses.hpp"
#include "SnPart.hpp"

#include "SnCGbank.hpp"
#include "SnCGproductFunctions.hpp"
//#include "SnCGcoefficient.hpp"
//class SnCGbank
//SnCGbank* _sncgbank=nullptr;

//#include "SnPartProduct.hpp"


using namespace cnine;
using namespace Snob2;


//int KroneckerCoefficient(const IntegerPartition& _mu1, const IntegerPartition& _mu2, const IntegerPartition& _mu3){
//return _sncgbank->coeff(_mu1,_mu2,_mu3);
//}

//typedef CscalarObj cscalar;
//typedef CtensorObj ctensor;



int main(int argc, char** argv){
  Snob2_session session;

  const int n=5;
  IntegerPartitions Lambda(n);

  for(auto p: Lambda) 
    for(auto q: Lambda){
      cout<<p<<"*"<<q<<"=";
      bool start=1;
      for(auto r: Lambda){
	int a=CGcoefficient(p,q,r);
	if(a>0){
	  if(!start) cout<<"+";
	  cout<<a<<"*"<<r;
	  start=0;
	}
      }
      cout<<endl;
    }
}

