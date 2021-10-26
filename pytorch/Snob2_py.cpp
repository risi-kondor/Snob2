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

//std::default_random_engine rndGen;
//#include "Snob_base.cpp"

Snob2::Snob2_session session;


PYBIND11_MODULE(TORCH_EXTENSION_NAME, m) {

  using namespace cnine;
  using namespace Snob2;
  namespace py=pybind11;


  pybind11::class_<IntegerPartition>(m,"IntegerPartition")
    .def(pybind11::init<vector<int> >())
    .def("height",&IntegerPartition::height)
    .def("getn",&IntegerPartition::getn)
    .def("__getitem__",static_cast<int(IntegerPartition::*)(const int)const>(&IntegerPartition::operator()))
    .def("__setitem__",&IntegerPartition::set)
    .def("str",&IntegerPartition::str,py::arg("indent")="")
    .def("__str__",&IntegerPartition::str,py::arg("indent")="");



  pybind11::class_<IntegerPartitions>(m,"IntegerPartitions")
    .def(pybind11::init<int>())
    //.def("height",&IntegerPartition::height)
    .def("__getitem__",&IntegerPartitions::operator[])
    //.def("str",&IntegerPartition::str,py::arg("indent")="")
    //.def("__str__",&IntegerPartition::str,py::arg("indent")="")
    ;



  pybind11::class_<YoungTableau>(m,"YoungTableau")
    .def(pybind11::init<const IntegerPartition&>())
    .def("getk",&YoungTableau::getk)
    .def("shape",&YoungTableau::shape)
    .def("at",static_cast<int(YoungTableau::*)(const int, const int) const>(&YoungTableau::at))
    //.def("__getitem__",static_cast<int(IntegerPartition::*)(const int)const>(&IntegerPartition::operator()))
    //.def("__setitem__",&IntegerPartition::set)
    .def("str",&YoungTableau::str,py::arg("indent")="")
    .def("__str__",&YoungTableau::str,py::arg("indent")="");



  pybind11::class_<StandardYoungTableaux>(m,"StandardYoungTableaux")
    .def(pybind11::init<const IntegerPartition&>())
    .def("__getitem__",&StandardYoungTableaux::operator[])
    ;



  pybind11::class_<Permutation>(m,"Permutation")

    .def(pybind11::init<int>())
    .def(pybind11::init<int,const fill_raw&>())
    .def(pybind11::init<int,const fill_identity&>())
    .def(pybind11::init<vector<int> >())

    .def_static("identity",static_cast<Permutation (*)(int)>(&Permutation::Identity))

    .def("getn",&Permutation::getn)
    .def("__getitem__",static_cast<int(Permutation::*)(const int) const>(&Permutation::operator()))
    //.def("__setitem__",&IntegerPartition::set)

    .def("__eq__",&Permutation::operator==)

    .def("__mul__",&Permutation::operator*)
    .def("__imul__",&Permutation::operator*=)

    .def("inv",&Permutation::inv)
    .def("__inv__",&Permutation::inv)

    .def("str",&Permutation::str,py::arg("indent")="")
    .def("__str__",&Permutation::str,py::arg("indent")="");



  pybind11::class_<SnElement>(m,"SnElement") // can do this with inheritance?

    .def(pybind11::init<int>())
    .def(pybind11::init<int,const fill_raw&>())
    .def(pybind11::init<int,const fill_identity&>())
    //.def(pybind11::init<vector<int> >()) // conflict with below
    .def(pybind11::init<const Permutation&>())

    .def_static("identity",static_cast<SnElement (*)(int)>(&SnElement::Identity))

    .def("getn",&SnElement::getn)
    .def("__getitem__",static_cast<int(SnElement::*)(const int) const>(&SnElement::operator()))
    //.def("__setitem__",&IntegerPartition::set)

    .def("__eq__",&SnElement::operator==)

    .def("__mul__",&SnElement::operator*)
    .def("__imul__",&SnElement::operator*=)

    .def("inv",&SnElement::inv)
    .def("__inv__",&SnElement::inv)

    .def("str",&SnElement::str,py::arg("indent")="")
    .def("__str__",&SnElement::str,py::arg("indent")="");



  pybind11::class_<SnCharacter>(m,"SnCharacter")
    .def(pybind11::init<int>())
    .def(pybind11::init<const IntegerPartition&>())

    .def("str",&SnIrrep::str,py::arg("indent")="")
    .def("__str__",&SnIrrep::str,py::arg("indent")="");
        


  pybind11::class_<SnIrrep>(m,"SnIrrep")
    .def(pybind11::init<int>())
    .def(pybind11::init<const IntegerPartition&>())

    .def("dim",&SnIrrep::dim)
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
    .def("index",static_cast<int(Sn::*)(const SnElement&) const>(&Sn::index))
    .def("random",&Sn::random)

    .def("ncclasses",&Sn::ncclasses)
    .def("cclass",&Sn::cclass)
    .def("index",static_cast<int(Sn::*)(const IntegerPartition&) const>(&Sn::index))
    .def("cclass_size",static_cast<int(Sn::*)(const IntegerPartition&) const>(&Sn::class_size))

    .def("irrep",&Sn::irrep)

    .def("str",&Sn::str,py::arg("indent")="")
    .def("__str__",&Sn::str,py::arg("indent")="");


}
