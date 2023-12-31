
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "Snob2_base.hpp"
#include <map>

#include "IntegerPartitions.hpp"

#include "SnElement.hpp"
#include "SnCClass.hpp"
#include "SnIrrepObj.hpp"
//#include "SnCharacter.hpp"

#include "SnOverSmObj.hpp"
//#include "SnModule.hpp"
//#include "SnRepresentation.hpp"

extern cnine::Factorial cnine::factorial;

namespace Snob2 {

// class SnClassFunction;

class SnObj {
public:
  friend class Sn;

  const int n;
  int order;

  SnObj *Snminus1 = nullptr;

  mutable vector<SnIrrepObj *> irreps;
  mutable map<IntegerPartition, SnIrrepObj *> irrep_map;

  mutable vector<SnCClass *> cclasses;
  mutable map<SnCClass, int> cclass_map;

  map<int, SnOverSmObj *> snsm_map;
  // SnModule module;
  // SnRepresentation repr;
  bool all_irreps = false;

public:
  SnObj(const int _n) : n(_n) {
    order = cnine::factorial(n);
    // cout<<"Creating Sn("<<n<<")"<<endl;
  }

  ~SnObj() {
    for (auto p : irreps)
      delete p;
    for (auto p : cclasses)
      delete p;
    for (auto &p : snsm_map)
      delete p.second;
  }

  static SnElement dummy_element() { return SnElement::Identity(1); }

public
    : // ---- Elements
      // -------------------------------------------------------------------------------------
  int size() const { return order; }

  SnElement identity() const { return SnElement(n, cnine::fill_identity()); }

  SnElement element(int e) const {
    SnElement p(n, cnine::fill_identity());

    vector<int> s(n);
    for (int i = n; i > 0; i--) {
      s[i - 1] = i - e / cnine::factorial(i - 1);
      e = e % cnine::factorial(i - 1);
    }

    for (int i = 2; i <= n; i++) {
      int t = s[i - 1];
      for (int k = i; k >= t + 1; k--)
        p[k - 1] = p[k - 2];
      p[t - 1] = i;
    }

    return p;
  }

  int index(const SnElement &sigma) const {
    if (n == 1)
      return 0;
    assert(sigma.size() == n);
    SnElement tau(n - 1, cnine::fill::raw);
    int a = 0;
    int i = 0;
    for (; i < n; i++) {
      if (sigma[i] == n) {
        a = n - i - 1;
        break;
      } else
        tau[i] = sigma[i];
    }
    i++;
    for (; i < n; i++)
      tau[i - 1] = sigma[i];
    // cout<<" "<<a<<" "<<tau<<endl;
    return Snminus1->index(tau) + a * cnine::factorial(n - 1);
  }

  SnElement random() const {
    uniform_int_distribution<int> distr(0, size() - 1);
    return element(distr(rndGen));
  }

public
    : // ---- Conjugacy classes
      // -------------------------------------------------------------------------
  const int ncclasses() const {
    make_cclasses();
    return cclasses.size();
  }

  SnCClass cclass(const int i) const {
    make_cclasses();
    return *cclasses[i];
  }

  const int index(const SnCClass &lambda) const {
    make_cclasses();
    return cclass_map[lambda];
  }

private:
  void make_cclasses() const {
    if (cclasses.size() > 0)
      return;
    IntegerPartitions Lambda(n);
    for (int i = 0; i < Lambda.size(); i++) {
      SnCClass c(Lambda[i]);
      cclasses.push_back(new SnCClass(c));
      cclass_map[c] = i;
    }
  }

public
    : // ---- Irreps
      // -------------------------------------------------------------------------------------
  /*
  SnIrrep irrep(const IntegerPartition& lambda){
    SNOB2_ASSERT(lambda.getn()==n,"Irrep index of Sn must be a partition of
  n."); return SnIrrep(get_irrep(lambda));
  }
  */

  SnIrrepObj *get_irrep(const IntegerPartition &lambda) const {
    auto it = irrep_map.find(lambda);
    if (it != irrep_map.end())
      return it->second;
    SnIrrepObj *irrep = new SnIrrepObj(lambda);
    irreps.push_back(irrep);
    irrep_map[lambda] = irrep;
    return irrep;
  }

  vector<SnIrrepObj *> get_all_irreps() const {
    make_all_irreps();
    return irreps;
  }

  /* depricated
  void make_ancestors(SnIrrepObj& irrep) const{
    if(irrep.ancestors.size()>0) return;
    assert(Snminus1);
    IntegerPartition lamb(irrep.lambda);
    for(int i=0; i<lamb.k-1; i++){
      if(lamb.p[i+1]==lamb.p[i]) continue;
      lamb.p[i]--;
      irrep.ancestors.push_back(Snminus1->get_irrep(lamb));
      lamb.p[i]++;
    }
    lamb.p[lamb.k-1]--;
    if(lamb.p[lamb.k-1]==0) lamb.k--;
    if(lamb.k>0)
      irrep.ancestors.push_back(Snminus1->get_irrep(lamb));
  }
  */

  /*
  SnModule get_module(){
    make_all_irreps();
    return module;
  }
  */

  // private:

  void make_all_irreps() const {
    if (all_irreps)
      return;
    IntegerPartitions partitions = IntegerPartitions(n);
    for (int i = 0; i < partitions.size(); i++) {
      get_irrep(partitions[i]);
    }
  }

public
    : // ---- Characters
      // ---------------------------------------------------------------------------------
  /*
  SnClassFunction* get_character(const IntegerPartition& lambda){
    auto it=character_map.find(lambda);
    if(it!=character_map.end()) return it->second;
    SnIrrepObj* chi=get_irrep(lambda)->get_character(); //=new
  SnIrrepObj(lambda); TODO character_map.push_back(chi);
    character_map[lambda]=chi;
    return chi;
  }
  */

public
    : // ---- SnOverSm
      // -----------------------------------------------------------------------------------
  SnOverSmObj *get_SnOverSm(const int m) {
    auto it = snsm_map.find(m);
    if (it != snsm_map.end())
      return it->second;
    SnOverSmObj *t = new SnOverSmObj(n, m);
    snsm_map[m] = t;
    return t;
  }
};

} // namespace Snob2
