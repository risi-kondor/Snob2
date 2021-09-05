#ifndef _Snob2_session
#define _Snob2_session

#include "CnineSession.hpp"


namespace Snob2{

  class Snob2_session{
  public:

    cnine::cnine_session* cnine_session=nullptr;


    Snob2_session(){
      cnine_session=new cnine::cnine_session();
      cout<<"Snob2 initialized."<<endl<<endl;
    }


    ~Snob2_session(){
      cout<<"Shutting down Snob2."<<endl;
      delete cnine_session;
    }
    
  };

}


#endif 
