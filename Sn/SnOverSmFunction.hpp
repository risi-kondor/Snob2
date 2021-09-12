#include "SnOverSm.hpp"
#include "FunctionOnGroup.hpp"
#include "RtensorObj.hpp"


namespace Snob2{

  class SnOverSmFunction: public FunctionOnGroup<SnOverSmObj,cnine::RtensorObj>{
  public:

    using FunctionOnGroup::FunctionOnGroup;

    template<typename FILLTYPE>
    SnOverSmFunction(int n, const FILLTYPE& fill):
      FunctionOnGroup<SnOverSmObj,cnine::RtensorObj>(_snbank->get_Sn(n),fill){}

    template<typename FILLTYPE>
    SnOverSmFunction(const SnOverSm& _G, const FILLTYPE& fill):
      FunctionOnGroup<SnOverSmObj,cnine::RtensorObj>(_G.obj,fill){}


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
