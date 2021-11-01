
// This file is part of Snob2, a symmetric group FFT library. 
// 
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.





pybind11::class_<SnFunction>(m,"SnFunction",
  "Function on Sn.")

  .def(pybind11::init<const int>())
  .def(pybind11::init<const int, const fill_raw&>())
  .def(pybind11::init<const int, const fill_zero&>())
  .def(pybind11::init<const int, const fill_ones&>())
  .def(pybind11::init<const int, const fill_gaussian&>())
  .def(pybind11::init<const int, const fill_sequential&>())

  .def_static("raw",static_cast<SnFunction (*)(const int, const int)>(&SnFunction::raw),
    py::arg("n"),py::arg("dev")=0)
  .def_static("zero",static_cast<SnFunction (*)(const int, const int)>(&SnFunction::zero),
    py::arg("n"),py::arg("dev")=0)
  .def_static("ones",static_cast<SnFunction (*)(const int, const int)>(&SnFunction::ones),
    py::arg("n"),py::arg("dev")=0)
  .def_static("gaussian",static_cast<SnFunction (*)(const int, const int)>(&SnFunction::gaussian),
    py::arg("n"),py::arg("dev")=0)
  .def_static("sequential",static_cast<SnFunction (*)(const int, const int)>(&SnFunction::sequential),
    py::arg("n"),py::arg("dev")=0)

  .def("__len__",&SnFunction::size,"Return the size of the function, i.e., the number of group elements.")

  .def("__getitem__",static_cast<float(SnFunction::*)(const int) const>(&SnFunction::get_value))
  .def("__getitem__",static_cast<float(SnFunction::*)(const SnElement&) const>(&SnFunction::get_value))

  .def("left_translate",&SnFunction::left_translate)
  .def("right_translate",&SnFunction::right_translate)
  .def("inv",&SnFunction::inv)
  .def("convolve",&SnFunction::convolve)

  .def("__str__",&SnFunction::str,py::arg("indent")="");



pybind11::class_<SnOverSmFunction>(m,"SnOverSmFunction",
  "Function on Sn/Sm.")

  .def(pybind11::init<const int, const int>())
  .def(pybind11::init<const int, const int, const fill_raw&>())
  .def(pybind11::init<const int, const int, const fill_zero&>())
  .def(pybind11::init<const int, const int, const fill_ones&>())
  .def(pybind11::init<const int, const int, const fill_gaussian&>())
  .def(pybind11::init<const int, const int, const fill_sequential&>())

  .def_static("raw",static_cast<SnOverSmFunction (*)(const int, const int, const int)>(&SnOverSmFunction::raw),
    py::arg("n"),py::arg("m"),py::arg("dev")=0)
  .def_static("zero",static_cast<SnOverSmFunction (*)(const int, const int, const int)>(&SnOverSmFunction::zero),
    py::arg("n"),py::arg("m"),py::arg("dev")=0)
  .def_static("ones",static_cast<SnOverSmFunction (*)(const int, const int, const int)>(&SnOverSmFunction::ones),
    py::arg("n"),py::arg("m"),py::arg("dev")=0)
  .def_static("gaussian",static_cast<SnOverSmFunction (*)(const int, const int, const int)>(&SnOverSmFunction::gaussian),
    py::arg("n"),py::arg("m"),py::arg("dev")=0)
  .def_static("sequential",static_cast<SnOverSmFunction (*)(const int, const int, const int)>(&SnOverSmFunction::sequential),
    py::arg("n"),py::arg("m"),py::arg("dev")=0)
  
  .def("__len__",&SnOverSmFunction::size,"Return the size of the function, i.e., the number of group elements.")
  
//.def("__getitem__",static_cast<float(SnOverSmFunction::*)(const int) const>(&SnOverSmFunction::get_value))
//.def("__getitem__",static_cast<float(SnOverSmFunction::*)(const SnElement&) const>(&SnOverSmFunction::get_value))

//  .def("left_translate",&SnOverSmFunction::left_translate)
//  .def("right_translate",&SnOverSmFunction::right_translate)
//  .def("inv",&SnOverSmFunction::inv)
//  .def("convolve",&SnOverSmFunction::convolve)

  .def("__str__",&SnOverSmFunction::str,py::arg("indent")="");



pybind11::class_<SnPart>(m,"SnPart",
  "Isotypic part of an Sn vector.")

  .def(pybind11::init<const IntegerPartition&, const int>())
  .def(pybind11::init<const IntegerPartition&, const int, const fill_raw&>())
  .def(pybind11::init<const IntegerPartition&, const int, const fill_zero&>())
  .def(pybind11::init<const IntegerPartition&, const int, const fill_ones&>())
  .def(pybind11::init<const IntegerPartition&, const int, const fill_identity&>())
  .def(pybind11::init<const IntegerPartition&, const int, const fill_gaussian&>())

  .def_static("raw",static_cast<SnPart (*)(const IntegerPartition&, const int, const int)>(&SnPart::raw),
    py::arg("lambd"), py::arg("m"),py::arg("dev")=0)
  .def_static("zero",static_cast<SnPart (*)(const IntegerPartition&, const int, const int)>(&SnPart::zero),
    py::arg("lambd"), py::arg("m"),py::arg("dev")=0)
  .def_static("ones",static_cast<SnPart (*)(const IntegerPartition&, const int, const int)>(&SnPart::identity),
    py::arg("lambd"), py::arg("m"),py::arg("dev")=0)
  .def_static("gaussian",static_cast<SnPart (*)(const IntegerPartition&, const int, const int)>(&SnPart::gaussian),
    py::arg("lambd"), py::arg("m"),py::arg("dev")=0)

  .def("apply",static_cast<SnPart (SnPart::*)(const SnElement&) const>(&SnPart::apply))
  .def("apply_inplace",static_cast<SnPart& (SnPart::*)(const SnElement&)>(&SnPart::apply_inplace))

  .def("__str__",&SnPart::str,py::arg("indent")="");



pybind11::class_<SnVec>(m,"SnVec",
  "Sn-covariant vector.")

  .def(pybind11::init<const SnType&>())
  .def(pybind11::init<const SnType&, const fill_raw&>())
  .def(pybind11::init<const SnType&, const fill_zero&>())
  .def(pybind11::init<const SnType&, const fill_ones&>())
  .def(pybind11::init<const SnType&, const fill_identity&>())
  .def(pybind11::init<const SnType&, const fill_gaussian&>())

  .def_static("raw",static_cast<SnVec (*)(const SnType&, const int)>(&SnVec::raw),
    py::arg("lambd"), py::arg("dev")=0)
  .def_static("zero",static_cast<SnVec (*)(const SnType&, const int)>(&SnVec::zero),
    py::arg("lambd"), py::arg("dev")=0)
  .def_static("ones",static_cast<SnVec (*)(const SnType&, const int)>(&SnVec::identity),
    py::arg("lambd"), py::arg("dev")=0)
  .def_static("gaussian",static_cast<SnVec (*)(const SnType&, const int)>(&SnVec::gaussian),
    py::arg("lambd"), py::arg("dev")=0)

  .def("apply",static_cast<SnVec (SnVec::*)(const SnElement&) const>(&SnVec::apply))
  .def("apply_inplace",static_cast<SnVec& (SnVec::*)(const SnElement&)>(&SnVec::apply_inplace))

  .def("__str__",&SnVec::str,py::arg("indent")="");



