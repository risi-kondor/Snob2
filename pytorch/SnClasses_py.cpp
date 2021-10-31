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

