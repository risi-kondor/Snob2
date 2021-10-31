#include <pybind11/stl.h>
#include <pybind11/complex.h>

#include "Snob2_base.cpp"
#include "Snob2_session.hpp"

#include "IntegerPartition.hpp"
#include "IntegerPartitions.hpp"
#include "YoungTableau.hpp"
#include "StandardYoungTableaux.hpp"
#include "Permutation.hpp"

#include "SnElement.hpp"
#include "SnIrrep.hpp"
#include "Sn.hpp"

#include "SnFunction.hpp"
#include "SnOverSmFunction.hpp"
#include "SnClassFunction.hpp"

//std::default_random_engine rndGen;
//#include "Snob_base.cpp"

// ":return: int" prints "Returns: "

Snob2::Snob2_session session;


PYBIND11_MODULE(TORCH_EXTENSION_NAME, m) {


  using namespace cnine;
  using namespace Snob2;
  namespace py=pybind11;

  py::options options;
  //options.disable_function_signatures();


  pybind11::class_<IntegerPartition>(m,"IntegerPartition",
    "Class to represent an integer partition (p_1,p_2,...,p_k) of n.")
    .def(pybind11::init<vector<int> >(),"Initialize from a list of integers.")
    .def("height",&IntegerPartition::height,"Return the number of parts, k.")
    .def("getn",&IntegerPartition::getn,"Return n.")
    .def("__getitem__",static_cast<int(IntegerPartition::*)(const int)const>(&IntegerPartition::operator()),
      "Return the the i'th part, p_i.")
    .def("__setitem__",&IntegerPartition::set, "Set the i'th part to x")
    //.def("str",&IntegerPartition::str,py::arg("indent")="")
    .def("__str__",&IntegerPartition::str,py::arg("indent")="",
      "Print the integer partition to string.");



  pybind11::class_<IntegerPartitions>(m,"IntegerPartitions",
    "This object represents all integer partitions of a given integer n.")
    .def(pybind11::init<int>(),"Create an object to represent all integer partitions of n.")
    .def("__getitem__",&IntegerPartitions::operator[],"Return the i'th integer partition.")
    .def("__len__",&IntegerPartitions::size,"Return the number of integer partition.")
    .def("at",&IntegerPartitions::operator[],"Return the i'th integer partition.")
    //.def("str",&IntegerPartition::str,py::arg("indent")="")
    //.def("__str__",&IntegerPartition::str,py::arg("indent")="")
    /*
    .def("__getitem__",[](const IntegerPartitions& obj, const py::slice& slice){
	size_t start, stop, step, slicelength;
	if (!slice.compute(obj.size(), &start, &stop, &step, &slicelength)) throw py::error_already_set();
	auto v=obj(start,stop+1);
	py::list R;
	for(auto& p:v){
	  py::object x=py::class_<IntegerPartition>(p);
	  R.append(x);
	  //R.append(py::cast(p));
	}
	return R;
      })
    */
    ;



  pybind11::class_<YoungTableau>(m,"YoungTableau")
    .def(pybind11::init<const IntegerPartition&>(),"Return a tableau of the given shape filled with 1,...,n")
    .def("getk",&YoungTableau::getk,"Return the number of rows.")
    .def("shape",&YoungTableau::shape,"Return the integer partition describing the shape of this tableau.")
    .def("at",static_cast<int(YoungTableau::*)(const int, const int) const>(&YoungTableau::at),
	 "Return the integer at position (i,j) in the tableau.")
    //.def("__getitem__",static_cast<int(IntegerPartition::*)(const int)const>(&IntegerPartition::operator()))
    //.def("__setitem__",&IntegerPartition::set)
    //.def("str",&YoungTableau::str,py::arg("indent")="")
    .def("__str__",&YoungTableau::str,py::arg("indent")="","Print the tableau to string.");



  pybind11::class_<StandardYoungTableaux>(m,"StandardYoungTableaux",
    "Class representing standard Young tableaux of a given shape.")
    .def(pybind11::init<const IntegerPartition&>())

    .def("__len__",&StandardYoungTableaux::size,"Return the number of standard Young tableaux.")
    .def("__getitem__",&StandardYoungTableaux::operator[],"")

    .def("__str__",&StandardYoungTableaux::str,py::arg("indent")="","Print object to string.");
    ;



  pybind11::class_<Permutation>(m,"Permutation",
    "Class to represent a permutation sigma of (1,2,...,n)")

    .def(pybind11::init<int>())
    .def(pybind11::init<int,const fill_raw&>())
    .def(pybind11::init<int,const fill_identity&>(),"Return the identity permutation on n items")
    .def(pybind11::init<vector<int> >(),"Initialize the permutation from a list.")

    .def_static("identity",static_cast<Permutation (*)(int)>(&Permutation::Identity),
      "Return the identity permutation of n.")

    .def("getn",&Permutation::getn,"Return n.")
    .def("__getitem__",static_cast<int(Permutation::*)(const int) const>(&Permutation::operator()),
      "Return sigma(i)")
    //.def("__setitem__",&IntegerPartition::set)

    .def("__eq__",&Permutation::operator==)

    .def("__mul__",&Permutation::operator*)
    .def("__imul__",&Permutation::operator*=)

    .def("inv",&Permutation::inv,"Return the inverse permutation.")
    .def("__inv__",&Permutation::inv)

    .def("str",&Permutation::str,py::arg("indent")="")
    .def("__str__",&Permutation::str,py::arg("indent")="");



  pybind11::class_<SnElement>(m,"SnElement",
    "Class to represent symmetric group elements.") // can do this with inheritance?

    .def(pybind11::init<int>())
    .def(pybind11::init<int,const fill_raw&>())
    .def(pybind11::init<int,const fill_identity&>())
    .def(pybind11::init<vector<int> >()) // conflict with below
    .def(pybind11::init<const Permutation&>())

    .def_static("identity",static_cast<SnElement (*)(int)>(&SnElement::Identity),"Return the identity element of Sn.")

    .def("getn",&SnElement::getn,"Return n.")
    .def("__getitem__",static_cast<int(SnElement::*)(const int) const>(&SnElement::operator()))
    //.def("__setitem__",&IntegerPartition::set)

    .def("__eq__",&SnElement::operator==)

    .def("__mul__",&SnElement::operator*)
    .def("__imul__",&SnElement::operator*=)

    .def("inv",&SnElement::inv)
    .def("__inv__",&SnElement::inv)

    //.def("str",&SnElement::str,py::arg("indent")="")
    .def("__str__",&SnElement::str,py::arg("indent")="");


  
  pybind11::class_<SnCClass>(m,"SnCClass",
    "Conjugacy class of Sn.")

    .def(pybind11::init<const IntegerPartition&>())

    .def("__str__",&SnCClass::str,py::arg("indent")="");




        
  pybind11::class_<SnCharacter>(m,"SnCharacter",
    "Class to represent characters of Sn.")

    .def(pybind11::init<const IntegerPartition&>(),
      "The character corresponding to the integer partition lambda.")

    //.def("str",&SnCharacter::str,py::arg("indent")="")
    .def("__str__",&SnCharacter::str,py::arg("indent")="");
        


  pybind11::class_<SnIrrep>(m,"SnIrrep",
    "Class to represent the irreps of Sn.")

    .def(pybind11::init<int>())
    .def(pybind11::init<const IntegerPartition&>())

    .def("get_dim",&SnIrrep::dim,"Return the dimension of the irrep")
    .def("__lt__",&SnIrrep::operator<)

    .def("__getitem__",&SnIrrep::operator())

    .def("str",&SnIrrep::str,py::arg("indent")="")
    .def("__str__",&SnIrrep::str,py::arg("indent")="");
        


  pybind11::class_<Sn>(m,"Sn")
    .def(pybind11::init<int>())

    .def("getn",&Sn::getn)
    .def("order",&Sn::size)
    .def("__len__",&Sn::size)
    
    .def("identity",&Sn::identity)
    .def("element",&Sn::element)
    .def("__getitem__",&Sn::element)
    .def("index",static_cast<int(Sn::*)(const SnElement&) const>(&Sn::index))
    .def("random",&Sn::random)

    .def("ncclasses",&Sn::ncclasses)
    .def("cclass",static_cast<SnCClass(Sn::*)(const int x) const>(&Sn::cclass))
    .def("cclass",static_cast<SnCClass(Sn::*)(const IntegerPartition&) const>(&Sn::cclass))
    .def("index",static_cast<int(Sn::*)(const IntegerPartition&) const>(&Sn::index))
    .def("cclass_size",static_cast<int(Sn::*)(const IntegerPartition&) const>(&Sn::class_size))
    .def("index",static_cast<int(Sn::*)(const SnCClass&) const>(&Sn::index))
    .def("cclass_size",static_cast<int(Sn::*)(const SnCClass&) const>(&Sn::class_size))

    .def("nchars",&Sn::nchars)
    .def("character",static_cast<SnClassFunction(Sn::*)(const IntegerPartition&) const>(&Sn::character))
    //.def("character",static_cast<SnClassFunction(Sn::*)(int) const>(&Sn::character))

    .def("irrep",&Sn::irrep)

    .def("str",&Sn::str,py::arg("indent")="")
    .def("__str__",&Sn::str,py::arg("indent")="");


#include "SnFunctions_py.cpp"

}

