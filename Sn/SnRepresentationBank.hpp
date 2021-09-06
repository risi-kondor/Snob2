#ifndef _SnRepresentationBank
#define _SnRepresentationBank

#include <map>

#include "SnRepresentationObj.hpp"

namespace Snob2{

  class SnRepresentationBank{
  public:

    map<SnType,SnRepresentationObj*> reps;

    ~SnRepresentationBank(){
      for(auto p:reps) delete p.second;
    }


  public:

    SnRepresentationObj* get_rep(const SnType& tau){
      if(reps.find(tau)==reps.end()) reps[tau]=new SnRepresentationObj(tau);
      return reps[tau];
    }

  };

}

#endif
