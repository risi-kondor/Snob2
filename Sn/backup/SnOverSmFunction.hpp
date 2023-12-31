
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "SnOverSm.hpp"
#include "FunctionOnGroup.hpp"
#include "RtensorObj.hpp"

namespace Snob2 {

class SnOverSmFunction : public cnine::RtensorObj {
  //: public FunctionOnGroup<SnOverSmObj,cnine::RtensorObj>{
public:
  using FunctionOnGroup::FunctionOnGroup;

  template <typename FILLTYPE>
  SnOverSmFunction(int n, int m, const FILLTYPE &fill, const int _dev = 0)
      : FunctionOnGroup<SnOverSmObj, cnine::RtensorObj>(
            _snbank->get_SnOverSm(n, m), fill, _dev) {}

  // template<typename FILLTYPE>
  // SnOverSmFunction(const SnOverSm& _G, const FILLTYPE& fill, const int
  // _dev=0): FunctionOnGroup<SnOverSmObj,cnine::RtensorObj>(_G.obj,fill,_dev){}

public
    : // ---- Named constructors
      // ------------------------------------------------------------------------
  SnOverSmFunction static raw(const int n, const int m, const int _dev = 0) {
    return SnOverSmFunction(n, m, cnine::fill_raw(), _dev);
  }

  SnOverSmFunction static zero(const int n, const int m, const int _dev = 0) {
    return SnOverSmFunction(n, m, cnine::fill_zero(), _dev);
  }

  SnOverSmFunction static gaussian(const int n, const int m,
                                   const int _dev = 0) {
    return SnOverSmFunction(n, m, cnine::fill_gaussian(), _dev);
  }

public
    : // ---- I/O
      // ---------------------------------------------------------------------------------------
  string str(const string indent = "") const {
    ostringstream oss;
    for (int i = 0; i < N; i++) {
      // oss<<G.element(i)<<" : ";  // Fix this!
      oss << RtensorObj::get_value(i) << endl;
    }
    return oss.str();
  }

  friend ostream &operator<<(ostream &stream, const SnOverSmFunction &x) {
    stream << x.str();
    return stream;
  }
};

} // namespace Snob2
