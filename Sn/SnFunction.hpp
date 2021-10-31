#ifndef _SnFunction
#define _SnFunction

#include "SnObj.hpp"
#include "RtensorObj.hpp"
//#include "FunctionOnGroup.hpp"


namespace Snob2{

  class SnFunction: public cnine::RtensorObj{
  public:

    typedef cnine::RtensorObj rtensor;

    const int n;
    int N;
    SnObj* G;

    template<typename FILLTYPE, typename = typename std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value, FILLTYPE>::type>
    SnFunction(int _n, const FILLTYPE& fill, const int _dev=0):
      rtensor({_snbank->get_Sn(_n)->order},fill,_dev), n(_n){
      G=_snbank->get_Sn(n);
      N=G->order;
    }

    SnFunction(const int _n):
      SnFunction(_n,cnine::fill_zero()){}



  public: // ---- Named constructors ------------------------------------------------------------------------


    SnFunction static raw(const int n, const int _dev=0){
      return SnFunction(n,cnine::fill_raw(),_dev);}

    SnFunction static zero(const int n, const int _dev=0){
      return SnFunction(n,cnine::fill_zero(),_dev);}

    SnFunction static ones(const int n, const int _dev=0){
      return SnFunction(n,cnine::fill_ones(),_dev);}

    SnFunction static gaussian(const int n, const int _dev=0){
      return SnFunction(n,cnine::fill_gaussian(),_dev);}

    SnFunction static sequential(const int n, const int _dev=0){
      return SnFunction(n,cnine::fill_sequential(),_dev);}


  public: // ---- Copying ------------------------------------------------------------------------------------


    SnFunction(const SnFunction& x):
      rtensor(x),
      n(x.n),
      N(x.N),
      G(x.G){
      cout<<"SnFunction copied"<<endl;
    }

    SnFunction(SnFunction&& x):
      rtensor(std::move(x)),
      n(x.n),
      N(x.N),
      G(x.G){
      cout<<"SnFunction moved"<<endl;
    }


  public: // ---- Conversions --------------------------------------------------------------------------------


    SnFunction(const int _n, const rtensor& M): 
      rtensor(M),
      n(_n),
      N(M.dims(0)),
      G(_snbank->get_Sn(_n)){}


  public: // ---- Access -------------------------------------------------------------------------------------


    int size() const{
      return dims(0);
    }
    
    float operator()(const int i) const{
      return rtensor::value(i);
    }

    float get_value(const int i) const{
      return rtensor::value(i);
    }

    SnFunction& set_value(const int i, const float v){
      rtensor::set_value(i,v);
      return *this;
    }

    float operator()(const SnElement& x) const{
      const SnObj& G=*_snbank->get_Sn(n);
      return rtensor::value(G.index(x));
    }

    float get_value(const SnElement& x) const{
      const SnObj& G=*_snbank->get_Sn(n);
      return rtensor::value(G.index(x));
    }

    SnFunction& set_value(const SnElement& x, const float v){
      const SnObj& G=*_snbank->get_Sn(n);
      rtensor::set_value(G.index(x),v);
      return *this;
    }


  public: // ---- Operations ---------------------------------------------------------------------------------


    SnFunction left_translate(const SnElement& t) const{
      SnFunction R(n,cnine::fill_raw());
      const SnObj& G=*_snbank->get_Sn(n);
      for(int i=0; i<N; i++)
	R.set_value(t*G.element(i),rtensor::value(i));
      return R;
    }

    SnFunction right_translate(const SnElement& t) const{
      SnFunction R(n,cnine::fill_raw());
      const SnObj& G=*_snbank->get_Sn(n);
      for(int i=0; i<N; i++)
	R.set_value(G.element(i)*t,rtensor::value(i));
      return R;
    }

    SnFunction convolve(const SnFunction& g) const{
      assert(g.n==n);
      SnFunction R(n,cnine::fill_raw());
      const SnObj& G=*_snbank->get_Sn(n);
      for(int i=0; i<N; i++){
	float t=0;
	auto sigma=G.element(i);
	for(int j=0; j<N; j++)
	  t+=(*this)(sigma*G.element(j).inv())*g(j);
	R.set_value(i,t);
      }
      return R;
    }

    SnFunction inv() const{
      SnFunction R(n,cnine::fill_raw());
      const SnObj& G=*_snbank->get_Sn(n);
      for(int i=0; i<N; i++)
	R.set_value(G.element(i).inverse(),rtensor::value(i));
      return R;
    }


  public: // ---- I/O --------------------------------------------------------------------------------------- 


    string str(const string indent="") const{
      ostringstream oss;
      const SnObj& G=*_snbank->get_Sn(n);
      for(int i=0; i<N; i++){
	oss<<G.element(i)<<" : ";
	oss<<rtensor::get_value(i)<<endl;
      }
      return oss.str();
    }

    friend ostream& operator<<(ostream& stream, const SnFunction& x){
      stream<<x.str(); return stream;
    }


  };


}


#endif 
