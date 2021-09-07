#ifndef _FunctionOnGroup
#define _FunctionOnGroup

#include "Group.hpp"
#include "Gdims.hpp"

namespace Snob2{

  template<typename GROUP, typename TENSOR>
  class FunctionOnGroup: public TENSOR{
  public:

    typedef cnine::Gdims Gdims;

    //typedef decltype(GROUP::identity()) ELEMENT; 
    typedef decltype(GROUP::dummy_element()) ELEMENT; 
    typedef decltype(TENSOR::dummy_scalar()) SCALAR; 
    //typedef decltype(TENSOR::value(0)) SCALAR; 

    const GROUP& G; 
    const int N;


  public:

    template<typename FILLTYPE>
    FunctionOnGroup(const GROUP& _G, const FILLTYPE& dummy): 
      TENSOR(Gdims({_G.size()}),dummy),
      G(_G), 
      N(_G.size()){}


  public: // Access 

    int size() const{
      return N;
    }

    
    SCALAR operator()(const int i) const{
      return TENSOR::value(i);
    }

    FunctionOnGroup& set_value(const int i, const SCALAR v){
      TENSOR::set_value(i,v);
      return *this;
    }

    SCALAR operator()(const ELEMENT& x) const{
      return TENSOR::value(G.index(x));
    }

    FunctionOnGroup& set_value(const ELEMENT& x, const SCALAR v){
      TENSOR::set_value(G.index(x),v);
      return *this;
    }


  public: // Operations 

    FunctionOnGroup left_translate(const ELEMENT& t) const{
      FunctionOnGroup R(G,cnine::fill_raw());
      for(int i=0; i<N; i++)
	R.set_value(t*G.element(i),TENSOR::value(i));
      return R;
    }

    FunctionOnGroup right_translate(const ELEMENT& t) const{
      FunctionOnGroup R(G,cnine::fill_raw());
      for(int i=0; i<N; i++)
	R.set_value(G.element(i)*t,TENSOR::value(i));
      return R;
    }

    FunctionOnGroup inv() const{
      FunctionOnGroup R(G,cnine::fill_raw());
      for(int i=0; i<N; i++)
	R.set_value(G.element(i).inverse(),TENSOR::value(i));
      return R;
    }


  public: // I/O

    string str(const string indent="") const{
      ostringstream oss;
      for(int i=0; i<N; i++)
	oss<<G.element(i)<<" : "<<TENSOR::get_value(i)<<endl;
      return oss.str();
    }

    friend ostream& operator<<(ostream& stream, const FunctionOnGroup& x){
      stream<<x.str(); return stream;
    }

  };

}

#endif
