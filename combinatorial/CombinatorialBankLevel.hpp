
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _CombinatorialBankLevel
#define _CombinatorialBankLevel

#include <unordered_map>

#include "IntegerPartition.hpp"
#include "IntegerPartitionObj.hpp"

namespace Snob2 {

class CombinatorialBankLevel {
public:
  const int n;
  CombinatorialBankLevel *sub = nullptr;

  vector<IntegerPartitionObj *> ip;
  unordered_map<IntegerPartition, IntegerPartitionObj *> ip_map;

  vector<IntegerPartition *> partitions;
  vector<IntegerPartition *> ROpartitions;

  ~CombinatorialBankLevel() {
    for (auto p : partitions)
      delete p;
    for (auto p : ROpartitions)
      delete p;
    for (auto p : ip)
      delete p;
  }

public:
  CombinatorialBankLevel() : n(1) {}

  CombinatorialBankLevel(const int _n, CombinatorialBankLevel *_sub)
      : n(_n), sub(_sub) {}

public: // Access
  const vector<IntegerPartition *> &get_IntegerPartitions() {
    if (partitions.size() == 0)
      make_partitions();
    return partitions;
  }

  const vector<YoungTableau *> &
  get_YoungTableaux(const IntegerPartition &lambda) {
    IntegerPartitionObj &obj = get_IntegerPartitionObj(lambda);
    return obj.get_YoungTableaux();
  }

  const vector<IntegerPartition *> &get_ROpartitions() {
    if (ROpartitions.size() == 0)
      make_ROpartitions();
    return ROpartitions;
  }

private:
  IntegerPartitionObj &get_IntegerPartitionObj(const IntegerPartition &lambda) {
    assert(lambda.getn() == n);
    auto it = ip_map.find(lambda);
    if (it != ip_map.end())
      return *it->second;

    IntegerPartitionObj *r = new IntegerPartitionObj(lambda);
    if (n > 1) {
      // cout<<string(8-n,' ')<<lambda<<endl;
      // for(int i=0; i<lambda.k; i++)
      for (int i = lambda.k - 1; i >= 0; i--)
        if (lambda.shortenable(i)) {
          IntegerPartition mu(lambda);
          mu.remove(i);
          r->parents.push_back(&sub->get_IntegerPartitionObj(mu));
        }
    }

    ip.push_back(r);
    ip_map[lambda] = r;
    return *r;
  }

  void make_partitions() {
    if (n == 1) {
      partitions.push_back(new IntegerPartition(1, cnine::fill_identity()));
      return;
    }
    const vector<IntegerPartition *> &sub_partitions =
        sub->get_IntegerPartitions();
    for (auto _p : sub_partitions) {
      IntegerPartition &p = *_p;
      int k = p.height();
      // cout<<" "<<k<<p<<endl;
      if (k == 1 || p(k - 2) > p(k - 1)) {
        IntegerPartition *newp = new IntegerPartition(p);
        newp->add(k - 1);
        partitions.push_back(newp);
        // p.remove(k);
      }
      IntegerPartition *newp = new IntegerPartition(p);
      newp->add(k);
      partitions.push_back(newp);
    }
  }

  void make_ROpartitions() {
    if (partitions.size() == 0)
      make_partitions();
    int N = partitions.size();
    vector<bool> used(N, 0);
    for (int i = 0; i < N; i++)
      if (!used[i])
        proposeRO(used, N, i);
  }

  void proposeRO(vector<bool> &used, const int N, const int i) {
    used[i] = true;
    const vector<IntegerPartitionObj *> &subs =
        get_IntegerPartitionObj(*partitions[i]).parents;
    for (int j = i + 1; j < N; j++) {
      if (used[j])
        continue;
      const vector<IntegerPartitionObj *> &jsubs =
          get_IntegerPartitionObj(*partitions[j]).parents;
      bool failed = false;
      for (auto jsub : jsubs)
        if (find(subs.begin(), subs.end(), jsub) == subs.end()) {
          failed = true;
          break;
        }
      if (!failed)
        proposeRO(used, N, j);
    }
    ROpartitions.push_back(new IntegerPartition(*partitions[i]));
  }
};

} // namespace Snob2

#endif

// vector<IntegerPartition> subs=partitions[i]->get_parents();
