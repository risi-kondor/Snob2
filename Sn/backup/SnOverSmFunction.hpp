#include "SnOverSm.hpp"
#include "FunctionOnGroup.hpp"
#include "RtensorObj.hpp"


namespace Snob2{

  class SnOverSmFunction: public cnine::RtensorObj{ 
    //:public FunctionOnGroup<SnOverSmObj,cnine::RtensorObj>{
  public:

    using FunctionOnGroup::FunctionOnGroup;

    template<typename FILLTYPE>
    SnOverSmFunction(int n, int m, const FILLTYPE& fill, const int _dev=0):
      FunctionOnGroup<SnOverSmObj,cnine::RtensorObj>(_snbank->get_SnOverSm(n,m),fill,_dev){}

    //template<typename FILLTYPE>
    //SnOverSmFunction(const SnOverSm& _G, const FILLTYPE& fill, const int _dev=0):
    //FunctionOnGroup<SnOverSmObj,cnine::RtensorObj>(_G.obj,fill,_dev){}


  public: // ---- Named constructors ------------------------------------------------------------------------


    SnOverSmFunction static raw(const int n, const int m, const int _dev=0){
      return SnOverSmFunction(n,m,cnine::fill_raw(),_dev);}

    SnOverSmFunction static zero(const int n, const int m, const int _dev=0){
      return SnOverSmFunction(n,m,cnine::fill_zero(),_dev);}

    SnOverSmFunction static gaussian(const int n, const int m, const int _dev=0){
      return SnOverSmFunction(n,m,cnine::fill_gaussian(),_dev);}



  public: // ---- I/O --------------------------------------------------------------------------------------- 


    string str(const string indent="") const{
      ostringstream oss;
      for(int i=0; i<N; i++){
	//oss<<G.element(i)<<" : ";  // Fix this!
	oss<<RtensorObj::get_value(i)<<endl;
      }
      return oss.str();
    }

    friend ostream& operator<<(ostream& stream, const SnOverSmFunction& x){
      stream<<x.str(); return stream;
    }


  };


}
