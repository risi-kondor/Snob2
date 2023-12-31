
// This file is part of Snob2, a symmetric group FFT library.
//
// Copyright (c) 2021, Imre Risi Kondor
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _ClausenFFTvecTmplt
#define _ClausenFFTvecTmplt

#include "ClausenFFTpartTmplt.hpp"
#include "SnFunction.hpp"
#include "FunctionOnGroup.hpp"
#include "SnMultiVec.hpp"

namespace Snob2 {

class ClausenFFTvecTmplt {
public:
  int n;
  ClausenFFTvecTmplt *next = nullptr;

  vector<ClausenFFTpartTmplt *> parts;
  map<IntegerPartition, int> parts_map;

public
    : // ---- Constructors
      // -------------------------------------------------------------------------------
  ClausenFFTvecTmplt(const ClausenFFTvecTmplt &x) = delete;
  ClausenFFTvecTmplt &operator=(const ClausenFFTvecTmplt &x) = delete;

public
    : // ---- Access
      // -------------------------------------------------------------------------------------
  ClausenFFTpartTmplt *get_part(const IntegerPartition &lambda) {
    if (parts_map.find(lambda) == parts_map.end()) {
      int ix = parts.size();
      ClausenFFTpartTmplt *p = new ClausenFFTpartTmplt(lambda, ix);
      parts.push_back(p);
      parts_map[lambda] = ix;
      return p;
    }
    return parts[parts_map[lambda]];
  }

  void add(ClausenFFTpartTmplt *part) {
    const IntegerPartition &lambda = part->irrep->lambda;
    if (parts_map.find(lambda) != parts_map.end()) {
      cerr << "Part already present" << endl;
      exit(1);
    }
    int ix = parts.size();
    parts.push_back(part);
    parts_map[lambda] = ix;
  }

public: // ---- Creating the transform
        // ---------------------------------------------------------------------
  ClausenFFTvecTmplt(const int _n) : n(_n) {
    auto seed = get_part(IntegerPartition({n}));
    seed->blocks.push_back(new ClausenFFTblockTmplt(0, 0, 0));
    seed->d = 1;
    seed->m = 1;
  }

  ClausenFFTvecTmplt(int s,
                     const ClausenFFTvecTmplt &prev) { // s is a dummy here
    n = prev.n + 1;

    for (int i = 0; i < prev.parts.size(); i++) {
      ClausenFFTpartTmplt &part = *prev.parts[i];
      IntegerPartition lambda = part.irrep->lambda;
      int k = lambda.k;
      int m = part.m;
      for (int i = 0; i < k; i++)
        if (i == 0 || lambda.p[i] < lambda.p[i - 1]) {
          lambda.p[i]++;
          get_part(lambda)->add(part);
          lambda.p[i]--;
        }
      lambda.add(k);
      get_part(lambda)->add(part);
    }
    const_cast<ClausenFFTvecTmplt &>(prev).next = this;
  }

public: // ---- Applying the transform
        // ---------------------------------------------------------------------
  SnMultiVec uptransform(const SnMultiVec &v) const {
    int N = v.getN();
    int newN = N / n;

    SnMultiVec w;
    for (auto p : parts) {
      auto q = new SnMultiPart(p->uptransform(v));
      for (int j = 0; j < n; j++) {
        q->irrep->apply_left(split1(q->view3(), newN, n).slice2(j),
                             ContiguousCycle(n - j, n));
      }
      /*
      for(int i=0; i<newN; i++)
        for(int j=0; j<n; j++){
          //cout<<i<<j<<endl;
          q->apply_inplace(ContiguousCycle(n-j,n),i*n+j);
        }
      */
      w.parts.push_back(q);
    }
    return w.reduce();
  }

  SnMultiVec downtransform(const SnMultiVec &V) const {
    int N = V.getN();
    int newN = N * (n + 1);

    SnMultiVec VV = V.broadcast(n + 1);

    for (auto q : VV.parts) {
      for (int j = 0; j < n + 1; j++)
        q->irrep->apply_left(split1(q->view3(), N, n + 1).slice2(j),
                             ContiguousCycle(n + 1, n + 1 - j));
    }

    /*
    for(int c=0; c<N; c++)
      for(int i=0; i<n+1; i++)
        VV.apply_inplace_inv(ContiguousCycle(n+1-i,n+1),c*(n+1)+i);
    */

    SnMultiVec R;
    for (int i = 0; i < parts.size(); i++)
      R.parts.push_back(new SnMultiPart(newN, parts[i]->irrep, parts[i]->m,
                                        cnine::fill::zero, 0));

    assert(next);
    int i = 0;
    for (auto p : next->parts) {
      const SnMultiPart &part = *VV.parts[i];
      for (auto q : p->blocks) {
        float c =
            ((float)part.irrep->d) / (R.parts[q->subix]->irrep->d * (n + 1));
        part.add_block_to_multi(q->ioffs, q->joffs, *R.parts[q->subix], c);
      }
      i++;
    }

    return R;
  }

public
    : // ---- I/O
      // ----------------------------------------------------------------------------------------
  string str(const string indent = "") const {
    ostringstream oss;
    oss << indent << "Level " << n << ":" << endl;
    for (int i = 0; i < parts.size(); i++) {
      oss << parts[i]->str(indent + "  ");
    }
    return oss.str();
  }

  friend ostream &operator<<(ostream &stream, const ClausenFFTvecTmplt &x) {
    stream << x.str();
    return stream;
  }
};

} // namespace Snob2

#endif
/*
 SnMultiVec* mpack(const SnVec& v){
   SnMultiVec* R=new SnMultiVec();
   R->vecs.push_back(new SnVec(v));
   return R;
 }
 */

// Deprecated
/*
FunctionOnGroup<Sn,rtensor> unpack(SnVecPack* V){
  int N=V->vecs.size();
  Sn G(n);
  FunctionOnGroup<Sn,rtensor> R(G,cnine::fill::ones);
  assert(R.size()==N);
  for(int i=0; i<N; i++)
    R.set_value(i,V->vecs[i]->parts[0]->get_value(0,0));
  return R;
}
*/

/*
SnMultiVec* downtransform(const SnMultiVec* V) const{
  int N=V->getN();
  int newN=N*(n+1);

  SnMultiVec VV=V->broadcast(n+1);

  for(int c=0; c<N; c++){
    for(int i=0; i<n+1; i++){
      VV.apply_inplace_inv(ContiguousCycle(n+1-i,n+1),c*(n+1)+i);
    }
  }

  SnMultiVec* R=new SnMultiVec();
  for(int i=0; i<parts.size(); i++){
    R->parts.push_back(new
SnMultiPart(newN,parts[i]->irrep,parts[i]->m,cnine::fill::zero,0));
  }

  assert(next);
  int i=0;
  for(auto p:next->parts){
    const SnMultiPart& part=*VV.parts[i];
    for(auto q:p->blocks){
      float c=((float)part.irrep->d)/(R->parts[q->subix]->irrep->d*(n+1));
      part.add_block_to_multi(q->ioffs,q->joffs,*R->parts[q->subix],c);
    }
    i++;
  }

  return R;
}
*/

// Deprecated
/*
SnVecPack* pack(const FunctionOnGroup<Sn,rtensor>& f){
  SnVecPack* R=new SnVecPack();
  int N=f.size();
  R->vecs.resize(N);
  SnIrrepObj* irrep=_snbank->get_irrep(IntegerPartition({1}));
  for(int i=0; i<N; i++)
    R->vecs[i]=new SnVec(new SnPart(irrep,f(i)));
  return R;
}
*/

// SnMultiVec* mpack(const SnVec& v){
// return new SnMultiVec(v);
// }

// SnFunction unpack(SnMultiVec* V){
// return V->as_function(n);
// }

// SnMultiVec* mpack(const SnFunction& f){
// return new SnMultiVec(f);
// }

/*
SnVecPack* uptransform(const SnVecPack* V) const{
  int N=V->vecs.size();
  int newN=N/n;
  SnVecPack* W=new SnVecPack();
  W->vecs.resize(newN);

  for(int c=0; c<newN; c++){

    SnVec* w=new SnVec();
    for(int i=0; i<parts.size(); i++){
      w->parts.insert(parts[i]->irrep->lambda,
        new SnPart(parts[i]->irrep,parts[i]->m,cnine::fill::zero,0));
    }

    for(int i=0; i<n; i++){
      SnVec u=uptransform(*V->vecs[c*n+i]);
      u.apply_inplace(ContiguousCycle(n-i,n));
      (*w).add(u);
    }

    W->vecs[c]=w;
  }

  return W;
}
*/

/*
SnMultiVec* uptransform(const SnMultiVec* V) const{
  int N=V->getN();
  int newN=N/n;

  SnMultiVec* w=new SnMultiVec(); // memory leak???
  for(auto p: parts){
    //cout<<p->get_lambda()<<endl;
    auto q=new SnMultiPart(p->uptransform(*V));
    //cout<<"before:"<<*q<<endl;
    for(int i=0; i<newN; i++)
      for(int j=0; j<n; j++){
        //cout<<i<<j<<endl;
        q->apply_inplace(ContiguousCycle(n-j,n),i*n+j);
      }
    //cout<<"after:"<<*q<<endl;
    w->parts.push_back(q);
  }
  return new SnMultiVec(w->reduce());
}
*/

/*
SnVecPack* pack(const FunctionOnGroup<SnOverSmObj,rtensor>& f){
  SnVecPack* R=new SnVecPack();
  int N=f.size();
  R->vecs.resize(N);
  SnIrrepObj* irrep=_snbank->get_irrep(IntegerPartition({1}));
  for(int i=0; i<N; i++)
    R->vecs[i]=new SnVec(new SnPart(irrep,f(i)));
  return R;
}

SnVecPack* pack(const SnFunction& f){
  SnVecPack* R=new SnVecPack();
  int N=f.size();
  R->vecs.resize(N);
  SnIrrepObj* irrep=_snbank->get_irrep(IntegerPartition({1}));
  for(int i=0; i<N; i++)
    R->vecs[i]=new SnVec(new SnPart(irrep,f(i)));
  return R;
}
*/

/*
SnFunction unpack(SnVecPack* V){
  int N=V->vecs.size();
  SnFunction R(n,cnine::fill::ones);
  assert(R.size()==N);
  for(int i=0; i<N; i++)
    R.set_value(i,V->vecs[i]->parts[0]->get_value(0,0));
  return R;
}

FunctionOnGroup<SnOverSmObj,rtensor> unpack(int m, SnVecPack* V){
  int N=V->vecs.size();
  FunctionOnGroup<SnOverSmObj,rtensor>
R(_snbank->get_SnOverSm(n,m),cnine::fill::ones); assert(R.size()==N); for(int
i=0; i<N; i++) R.set_value(i,V->vecs[i]->parts[0]->get_value(0,0)); return R;
}
*/

/*
SnVec uptransform(const SnVec& v) const{
  SnVec w;
  for(auto p:parts){
    w.parts.push_back(new SnPart(p->uptransform(v)));
  }
  return w;
}
*/

/*
SnVecPack* downtransform(const SnVecPack* V) const{
  int N=V->vecs.size();
  int newN=N*(n+1);
  SnVecPack* W=new SnVecPack();
  W->vecs.resize(newN);

  for(int c=0; c<N; c++){
    for(int i=0; i<n+1; i++){
      //cout<<"i="<<i<<endl;

      //SnVec* w=new SnVec();
      //for(int j=0; j<parts.size(); j++){
      //w->parts.push_back(new
SnPart(parts[j]->irrep,parts[j]->m,cnine::fill::zero,0));
      //}

      SnVec u(*V->vecs[c]);
      u.apply_inplace_inv(ContiguousCycle(n+1-i,n+1));

      W->vecs[c*(n+1)+i]=new SnVec(downtransform(u));

    }
  }

  return W;
}
*/

/*
SnVec downtransform(const SnVec& v) const{

  SnVec w;
  for(int i=0; i<parts.size(); i++){
    w.parts.push_back(new
SnPart(parts[i]->irrep,parts[i]->m,cnine::fill::zero,0));
  }

  assert(next);
  int i=0;
  for(auto p:next->parts){
    const SnPart& part=*v.parts[i];
    for(auto q:p->blocks){
      float c=((float)part.irrep->d)/(w.parts[q->subix]->irrep->d*(n+1));
      part.add_block_to(q->ioffs,q->joffs,*w.parts[q->subix],c);
    }
    i++;
  }

  return w;
  }
*/

/*
SnVecPack* pack(const SnVec& v){
  SnVecPack* R=new SnVecPack();
  R->vecs.push_back(new SnVec(v));
  return R;
}
*/
