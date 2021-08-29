#ifndef _ProductGroupElement
#define _ProductGroupElement

#include "Snob2_base.hpp"
#include "Group.hpp"


namespace Snob2{

  template<typename E1, typename E2>
  class ProductGroupElement: public GroupElement{
  public:

    const E1 e1;
    const E2 e2;

  public:

    ProductGroupElement(const E1& _e1, const E2& _e2):
      e1(_e1), e2(_e2){}


  public:

    int index() const{
      return e1.index()*e2.size()+e2.index();
    }

    ProductGroupElement inverse() const{
      return ProductGroupElement(e1.inverse(),e2.inverse());
    }

    ProductGroupElement operator*(const ProductGroupElement& y) const{
      return ProductGroupElement(e1*y.e1,e2*y.e2);
    }


  public: // I/O

    string str(const string indent="") const{
      return "("+e1.str()+","+e2.str()+")";
    }

    friend ostream& operator<<(ostream& stream, const ProductGroupElement& x){
      stream<<x.str(); return stream;
    }


  };


  template<typename E1, typename E2, 
	   typename = typename std::enable_if<std::is_base_of<GroupElement,E1>::value, E1>::type>
  ProductGroupElement<E1,E2> operator*(const E1& e1, const E2& e2){
    return ProductGroupElement<E1,E2>(e1,e2);
  }


  template<typename E1, typename E2>
  inline ProductGroupElement<E1,E2> gpair(const E1& e1, const E2& e2){
    return ProductGroupElement<E1,E2>(e1,e2);
  }

}

#endif
