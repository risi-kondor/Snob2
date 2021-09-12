#ifndef _Snob2_session
#define _Snob2_session

#include "CnineSession.hpp"
#include "Snob2_base.hpp"
#include "CombinatorialClasses.hpp"
#include "SnClasses.hpp"


namespace Snob2{

  class Snob2_session{
  public:

    cnine::cnine_session* cnine_session=nullptr;


    Snob2_session(){

      cnine_session=new cnine::cnine_session();

      if(_combibank){cout<<"Only one CombinatorialClasses object can be defined."<<endl; return;}
      _combibank=new CombinatorialBank();

      if(_snbank){cout<<"Only one SnClasses object can be defined."<<endl; return;}
      _snbank=new SnBank();

      _snrepbank=new SnRepresentationBank();

      cout<<"Snob2 initialized."<<endl<<endl;

    }


    ~Snob2_session(){
      cout<<endl<<"Shutting down Snob2."<<endl;
      delete cnine_session;
    }
    
  };

}


#endif 
