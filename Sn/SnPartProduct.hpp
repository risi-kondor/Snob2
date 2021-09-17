#ifndef _SnPartProduct
#define _SnPartProduct

#include "SnVec.hpp"
#include "SnWeights.hpp"


namespace Snob2{

  class SnPartProduct{
  public:
    
    int n;

    const SnPart& x;
    const SnPart& y;


  public: // ---- Constructors -------------------------------------------------------------------------------

    
    SnPartProduct(const SnPart& _x, const SnPart& _y): x(_x), y(_y){
      n=x.getn();
    };


  public: // ---- CG-product ---------------------------------------------------------------------------------

    
    operator SnVec() const{
      if(n==1){
	return SnVec(new SnPart(_snbank->get_irrep({1}),x(0,0)*y(0,0)));
      }
      
      SnVec xsub=SnVec::down(x);
      SnVec ysub=SnVec::down(y);

      vector<SnVec> subs;
      for(auto p:xsub.parts)
	for(auto q:ysub.parts)
	  subs.push_back(SnVec(SnPartProduct(*p,*q)));
      SnVec sub=SnVec::concat(subs);
      SnWeights* W=_sncgbank->get(x.get_lambda(),y.get_lambda());
      return (*W)*sub;
    }
 

  public:


  };

}

#endif
