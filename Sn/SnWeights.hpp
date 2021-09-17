#ifndef _SnWeights
#define _SnWeights

#include "SnVec.hpp"
#include "RtensorObj_funs.hpp"


namespace Snob2{

  class SnWeights{
  public:

    typedef cnine::RtensorObj rtensor;

    unordered_map<IntegerPartition,rtensor*> weights;

    ~SnWeights(){
      for(auto p:weights)
	delete p.second;
    }


  public: // ---- Constructors -------------------------------------------------------------------------------


    template<typename FILLTYPE>
    SnWeights(const SnVec& x, const SnVec& y, const FILLTYPE& fill){
      assert(x.parts.size()==y.parts.size());
      for(int i=0; i<x.parts.size(); i++){
	const SnPart& xp=*x.parts[i];
	const SnPart& yp=*y.parts[i];
	assert(xp.get_lambda()==yp.get_lambda());
	rtensor* mx=new rtensor(cnine::dims(xp.dims(1)*yp.dims(1)),fill);
	weights[xp.get_lambda()]=mx;
      }
    }

    
  public: // ---- Access -------------------------------------------------------------------------------------


    rtensor get_matrix(const IntegerPartition& lambda) const{
      auto it=weights.find(lambda);
      assert(it!=weights.end());
      return *it->second;
    }

    rtensor* get_matrixp(const IntegerPartition& lambda){
      auto it=weights.find(lambda);
      assert(it!=weights.end());
      return it->second;
    }


  public: // ---- Operations ---------------------------------------------------------------------------------

    SnVec operator*(const SnVec& y) const{
      SnVec R;
      for(auto p:y.parts){
	R.parts.push_back(new SnPart(p->irrep,get_matrix(p->get_lambda())*(*p)));
      }
      return R;
    }


  };

}

#endif
