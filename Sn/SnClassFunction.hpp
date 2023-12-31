
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "RtensorObj.hpp"
#include "SnObj.hpp"

namespace Snob2 {

class SnClassFunction : public cnine::RtensorObj {
public:
  typedef cnine::RtensorObj rtensor;

  using rtensor::get_value;
  using rtensor::rtensor;
  using rtensor::set_value;

  int n;

  template <typename FILLTYPE,
            typename = typename std::enable_if<
                std::is_base_of<cnine::fill_pattern, FILLTYPE>::value,
                FILLTYPE>::type>
  SnClassFunction(int _n, const FILLTYPE &fill, const int _dev = 0)
      : rtensor({_snbank->get_Sn(_n)->ncclasses()}, fill, _dev), n(_n) {}

  SnClassFunction(const int _n) : SnClassFunction(_n, cnine::fill_zero()) {}

public
    : // ---- Named constructors
      // ------------------------------------------------------------------------
  SnClassFunction static raw(const int n, const int _dev = 0) {
    return SnClassFunction(n, cnine::fill_raw(), _dev);
  }

  SnClassFunction static zero(const int n, const int _dev = 0) {
    return SnClassFunction(n, cnine::fill_zero(), _dev);
  }

  SnClassFunction static ones(const int n, const int _dev = 0) {
    return SnClassFunction(n, cnine::fill_ones(), _dev);
  }

  SnClassFunction static gaussian(const int n, const int _dev = 0) {
    return SnClassFunction(n, cnine::fill_gaussian(), _dev);
  }

  SnClassFunction static sequential(const int n, const int _dev = 0) {
    return SnClassFunction(n, cnine::fill_sequential(), _dev);
  }

public
    : // ---- Access
      // ------------------------------------------------------------------------------------
  int size() const { return dim(0); }

  float operator()(const IntegerPartition &lambda) const {
    return rtensor::get_value(_snbank->get_Sn(lambda.getn())->index(lambda));
  }

  float operator()(const int i) const { return rtensor::get_value(i); }

  float get_value(const SnCClass &lambda) const {
    return rtensor::get_value(_snbank->get_Sn(lambda.getn())->index(lambda));
  }

  float get_value(const IntegerPartition &lambda) const {
    return rtensor::get_value(_snbank->get_Sn(lambda.getn())->index(lambda));
  }

  float get_value(const int i) const { return rtensor::get_value(i); }

  void set_value(const IntegerPartition &lambda, const float v) {
    rtensor::set_value(_snbank->get_Sn(lambda.getn())->index(lambda), v);
  }

  void set_value(const int i, const float v) { rtensor::set_value(i, v); }

public
    : // ---- I/O
      // ---------------------------------------------------------------------------------------
  string str(const string indent = "") const {
    ostringstream oss;
    SnObj *Gobj = _snbank->get_Sn(n);
    for (int i = 0; i < dims(0); i++) {
      oss << indent << Gobj->cclass(i) << " : ";
      oss << RtensorObj::get_value(i) << endl;
    }
    return oss.str();
  }

  friend ostream &operator<<(ostream &stream, const SnClassFunction &x) {
    stream << x.str();
    return stream;
  }
};

} // namespace Snob2
