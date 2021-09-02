#ifndef _SnIrrep
#define _SnIrrep

#include "SnIrrepObj.hpp"
#include "SnBank.hpp"


namespace Snob2{

  typedef cnine::RtensorObj rtensor;


  class SnIrrep{
  public:

    const SnIrrepObj* obj;
    IntegerPartition lambda;


  public:

    SnIrrep(){}

    SnIrrep(const SnIrrepObj* _obj):
      obj(_obj), lambda(_obj->lambda){}

    SnIrrep(const IntegerPartition& _lambda): lambda(_lambda){
      obj=_snbank->get_Sn(_lambda.getn())->get_irrep(_lambda);
    }

  public: // Access

    int dim() const{
      return obj->d;
    }


  public: 

    rtensor operator()(const SnElement& sigma) const{
      rtensor R(cnine::dims(obj->d,obj->d),cnine::fill::identity);
      obj->apply_left(R,sigma);
      return R;
    }


  public:

    string str(const string indent="") const{
      return "SnIrrep("+lambda.str()+")";
    }

    friend ostream& operator<<(ostream& stream, const SnIrrep& x){
      stream<<x.str(); return stream;
    }

  };

}

#endif
