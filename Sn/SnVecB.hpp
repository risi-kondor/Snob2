
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2022, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "SnPartB.hpp"
#include "SnType.hpp"
#include "SnRepresentation.hpp"
#include "associative_container.hpp"

namespace Snob2 {

class SnVecB : public cnine::associative_container<IntegerPartition, SnPartB> {
public:
  // indexed_mapB<IntegerPartition,SnPart> parts;

  ~SnVecB() {}

public
    : // ---- Constructors
      // --------------------------------------------------------------------------------
  SnVecB() {}

  template <typename FILLTYPE,
            typename = typename std::enable_if<
                std::is_base_of<cnine::fill_pattern, FILLTYPE>::value,
                FILLTYPE>::type>
  SnVecB(const SnType &_type, const FILLTYPE &fill, const int _dev = 0) {
    for (auto &p : _type)
      insert(p.first, new SnPartB(p.first, p.second, fill, _dev));
  }

  template <typename FILLTYPE,
            typename = typename std::enable_if<
                std::is_base_of<cnine::fill_pattern, FILLTYPE>::value,
                FILLTYPE>::type>
  SnVecB(const int b, const SnType &_type, const FILLTYPE &fill,
         const int _dev = 0) {
    for (auto &p : _type)
      insert(p.first, new SnPartB(b, p.first, p.second, fill, _dev));
  }

  // template<typename FILLTYPE, typename = typename
  // std::enable_if<std::is_base_of<cnine::fill_pattern, FILLTYPE>::value,
  // FILLTYPE>::type> SnVecB(const SnRepresentation& M, const FILLTYPE& fill,
  // const int _dev=0): SnVecB(M.obj,fill,_dev){}

  SnVecB(const SnType &_type, const int _dev = 0)
      : SnVecB(_type, cnine::fill_raw(), _dev) {}

  SnVecB(SnPartB *part) { insert(part->get_lambda(), part); }

public
    : // ---- Named constructors
      // -------------------------------------------------------------------------
  static SnVecB raw(const SnType &_type, const int _dev = 0) {
    return SnVecB(_type, cnine::fill::raw, _dev);
  }

  static SnVecB zero(const SnType &_type, const int _dev = 0) {
    return SnVecB(_type, cnine::fill::zero, _dev);
  }

  static SnVecB identity(const SnType &_type, const int _dev = 0) {
    return SnVecB(_type, cnine::fill::identity, _dev);
  }

  static SnVecB gaussian(const SnType &_type, const int _dev = 0) {
    return SnVecB(_type, cnine::fill::gaussian, _dev);
  }

  static SnVecB raw(const int b, const SnType &_type, const int _dev = 0) {
    return SnVecB(b, _type, cnine::fill::raw, _dev);
  }

  static SnVecB zero(const int b, const SnType &_type, const int _dev = 0) {
    return SnVecB(b, _type, cnine::fill::zero, _dev);
  }

  static SnVecB identity(const int b, const SnType &_type, const int _dev = 0) {
    return SnVecB(b, _type, cnine::fill::identity, _dev);
  }

  static SnVecB gaussian(const int b, const SnType &_type, const int _dev = 0) {
    return SnVecB(b, _type, cnine::fill::gaussian, _dev);
  }

public
    : // ---- Copying
      // ------------------------------------------------------------------------------------
  SnVecB(const SnVecB &x)
      : cnine::associative_container<IntegerPartition, SnPartB>(
            x){SNOB2_COPY_WARNING()}

        SnVecB(SnVecB && x)
      : cnine::associative_container<IntegerPartition, SnPartB>(std::move(x)) {
    SNOB2_MOVE_WARNING()
  }

  // SnVecB& operator=(const SnVecB& x){
  // SNOB2_ASSIGN_WARNING()
  // parts=x.parts;
  // return *this;
  // }

  // SnVecB& operator=(SnVecB&& x){
  // SNOB2_MOVEASSIGN_WARNING()
  // parts=std::move(x.parts);
  // return *this;
  // }

public
    : // ---- Access
      // -------------------------------------------------------------------------------------
  int getn() const {
    assert(size() > 0);
    return first().getn();
  }

  int getb() const {
    assert(size() > 0);
    return first().getb();
  }

  // int index(const IntegerPartition& lambda) const{
  // for(int i=0; i<parts.size(); i++)
  // if(parts[i]->irrep->lambda==lambda) return i;
  // return -1;
  // }

  SnType get_type() const {
    SnType R;
    for (auto p : *this)
      R.set(p.get_lambda(), p.getm());
    return R;
  }

public
    : // ---- Operations
      // ---------------------------------------------------------------------------------
  SnVecB apply(const SnElement &sigma) const {
    SnVecB R;
    for (auto p : *this) {
      SnPartB *A = new SnPartB(p);
      A->apply_inplace(sigma);
      R.insert(p.get_lambda(), A);
    }
    return R;
  }

  SnVecB &apply_inplace(const SnElement &sigma) {
    for (auto p : *this)
      p.apply_inplace(sigma);
    return *this;
  }

  SnVecB &apply_inplace(const ContiguousCycle &cyc) {
    for (auto p : *this)
      p.apply_inplace(cyc);
    return *this;
  }

  SnVecB apply(const Transposition &x) {
    SnVecB R;
    for (auto p : *this)
      R.insert(p.get_lambda(), p.apply(x));
    return R;
  }

public
    : // ---- Cumulative operations
      // ----------------------------------------------------------------------
  /*
  void add(const SnVecB& y){
    assert(size()==y.size());
    for(int i=0; i<parts.size(); i++)
      parts[i]->add(*y.parts[i]);
  }
  */

  void accumulate_up(SnType &offs, const SnVecB &sub, const SnType &tau,
                     const string indent = "") {
    // cout<<indent<<"Accumulate up "<<sub.get_type()<<" into
    // "<<get_type()<<endl;
    SnType sub_offs;
    for (auto &p : tau) {
      IntegerPartition lamb = p.first;
      assert(exists(lamb));
      SnPartB &target = (*this)[lamb];
      int ncols = p.second;
      int roffs = 0;
      int coffs = offs[lamb];
      lamb.foreach_sub([&](const IntegerPartition &mu) {
        assert(sub.exists(mu));
        const SnPartB &source = sub[mu];
        int nrows = source.getd();
        target.block3(0, roffs, coffs, -1, nrows, ncols)
            .add(source.block3(0, 0, sub_offs[mu], -1, nrows, ncols));
        sub_offs[mu] += ncols;
        roffs += nrows;
      });
      offs[lamb] += ncols;
    }
    // cout<<indent<<"."<<endl;
  }

public
    : // ---- Operations
      // ---------------------------------------------------------------------------------
  // SnVecB down() const{ // TODO
  // SNOB2_UNIMPL();
  // return *this;
  // }

  SnVecB static down(const SnPartB &v) {
    SnVecB R;
    int offs = 0;
    int m = v.getm();
    int b = v.getb();
    v.get_lambda().foreach_sub([&](const IntegerPartition &lambda) {
      auto P = new SnPartB(b, lambda, m, cnine::fill::zero);
      P->add(v.block3(0, offs, 0, b, P->getd(), m));
      R.insert(lambda, P);
      offs += P->getd();
    });
    return R;
  }

  SnVecB static up(const SnType &tau, const SnVecB &v) {
    int b = v.getb();
    SnVecB R(b, tau, cnine::fill_zero());
    SnType offs;
    for (auto &p : tau) {
      SnPartB &dest = R[p.first];
      int m = dest.getm();
      int voffs = 0;
      p.first.foreach_sub([&](const IntegerPartition &mu) {
        dest.block3(0, voffs, 0).add(v[mu].block3(0, 0, offs[mu], -1, -1, m));
        voffs += v[mu].getd();
        offs[mu] += m;
      });
    }
    return R;
  }

public
    : // ---- Fourier transforms
      // ------------------------------------------------------------------------
public
    : // ---- I/O
      // ---------------------------------------------------------------------------------------
  string str(string indent = "") const {
    ostringstream oss;
    for (auto p : *this) {
      oss << p << endl;
    }
    return oss.str();
  }

  friend ostream &operator<<(ostream &stream, const SnVecB &x) {
    stream << x.str();
    return stream;
  }
};

inline SnVecB operator*(const SnElement &sigma, const SnVecB &v) {
  return v.apply(sigma);
}

inline int sameb(const SnVecB &x, const SnVecB &y) {
  assert(x.getb() == y.getb());
  return x.getb();
}

inline int sameb(const SnVecB &x, const SnVecB &y, const SnVecB &z) {
  assert(x.getb() == y.getb());
  assert(x.getb() == z.getb());
  return x.getb();
}

inline int sameb(const SnVecB &x, const SnPartB &y, const SnPartB &z) {
  assert(x.getb() == y.getb());
  assert(x.getb() == z.getb());
  return x.getb();
}

} // namespace Snob2

/*
SnVecB static cat(const vector<SnVecB>& v){
  SnType tau;
  for(int i=0; i<v.size(); i++)
    for(auto p: v[i].parts)
      tau.add(p->get_lambda(),p->getm());
  SnVecB R(tau,cnine::fill::zero);
  vector<int> offs(R.parts.size(),0);
  for(int i=0; i<v.size(); i++)
    for(auto p: v[i].parts){
      int ix=R.index(p->irrep->lambda);
      R.parts[ix]->add_to_block(0,offs[ix],*p);
      offs[ix]+=p->dims(1);
    }
  return R;
}
*/
