pybind11::class_<ClausenFFT>(m,"ClausenFFT",
  "Clausen's FFT.")

  .def(pybind11::init<const int>())
  .def(pybind11::init<const int, const int>())

  .def("__call__",static_cast<SnVec (ClausenFFT::*)(const SnFunction&) const>(&ClausenFFT::operator()))
  .def("__call__",static_cast<SnVec (ClausenFFT::*)(const SnOverSmFunction&) const>(&ClausenFFT::operator()))

  .def("inv",&ClausenFFT::inv,"")
  .def("inv_snsm",&ClausenFFT::inv,"")

  .def("__str__",&ClausenFFT::str,py::arg("indent")="");

