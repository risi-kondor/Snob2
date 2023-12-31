
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

pybind11::class_<ClausenFFT>(m, "ClausenFFT", "Clausen's FFT.")

    .def(pybind11::init<const int>())
    .def(pybind11::init<const int, const int>())

    .def("__call__",
         static_cast<SnVec (ClausenFFT::*)(const SnFunction &) const>(
             &ClausenFFT::operator()))
    .def("__call__",
         static_cast<SnVec (ClausenFFT::*)(const SnOverSmFunction &) const>(
             &ClausenFFT::operator()))

    .def("inv", &ClausenFFT::inv, "")
    .def("inv_snsm", &ClausenFFT::inv, "")

    .def("__str__", &ClausenFFT::str, py::arg("indent") = "");
