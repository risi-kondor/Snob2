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
      //cout<<"n="<<n<<endl;
    };


  public: // ---- CG-product ---------------------------------------------------------------------------------

    
    operator SnVec() const{
      if(n==1){
	return SnVec(new SnPart(_snbank->get_irrep({1}),x(0,0)*y(0,0)));
      }

      SnVec xsub=SnVec::down(x);
      SnVec ysub=SnVec::down(y);

      //cout<<xsub<<endl; 
      //return SnVec();

      vector<SnVec> subs;
      for(auto p:xsub.parts)
	for(auto q:ysub.parts){
	  //cout<<"<"<<p->irrep->lambda<<","<<q->irrep->lambda<<">"<<endl;
	  subs.push_back(SnVec(SnPartProduct(*p,*q)));
	}
      SnVec sub=SnVec::cat(subs);
      //cout<<sub<<endl;
      SnType* tau=_sncgbank->get_type(x.get_lambda(),y.get_lambda());
      SnWeights* W=_sncgbank->getW(x.get_lambda(),y.get_lambda());
      return SnVec::up(*tau,(*W)*sub);
    }
 

  public:


  };

}

#endif
