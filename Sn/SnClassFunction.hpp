#ifndef _SnClassFunction
#define _SnClassFunction

#include "RtensorObj.hpp"


namespace Snob2{

  class SnClassFunction: public cnine::RtensorObj{
  public:

    typedef cnine::RtensorObj rtensor;

    using rtensor::rtensor;

    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnFunction(int n, const FILLTYPE& fill, const int _dev=0):
      FunctionOnGroup<SnObj,cnine::RtensorObj>({_snbank->get_Sn(n)->ncclasses()},fill,_dev){}


    
  public: // ---- Named constructors ------------------------------------------------------------------------


    SnFunction static raw(const int n, const int _dev=0){
      return SnClassFunction(n,cnine::fill_raw(),_dev);}

    SnFunction static zero(const int n, const int _dev=0){
      return SnClassFunction(n,cnine::fill_zero(),_dev);}

    SnFunction static gaussian(const int n, const int _dev=0){
      return SnClassFunction(n,cnine::fill_gaussian(),_dev);}


  public: // ---- I/O --------------------------------------------------------------------------------------- 


    string str(const string indent="") const{
      ostringstream oss;
      for(int i=0; i<dims(0); i++){
	//oss<<G.element(i)<<" : ";  // Fix this!
	oss<<RtensorObj::get_value(i)<<endl;
      }
      return oss.str();
    }

    friend ostream& operator<<(ostream& stream, const SnFunction& x){
      stream<<x.str(); return stream;
    }

  };

}

#endif
