#ifndef _ClausenFFTpartTmplt
#define _ClausenFFTpartTmplt

#include "ClausenFFTblockTmplt.hpp"
#include "SnVec.hpp"

namespace Snob2{

  class ClausenFFTpartTmplt{
  public:

    int index=0;
    int d=0;
    int m=0;
    SnIrrepObj* irrep;
    vector<ClausenFFTblockTmplt*> blocks;


  public: // ---- Constructors -------------------------------------------------------------------------------


    ClausenFFTpartTmplt(const IntegerPartition& lambda, const int _index):
      index(_index), irrep(_snbank->get_irrep(lambda)){}

    ClausenFFTpartTmplt(const ClausenFFTpartTmplt& x)=delete;
    ClausenFFTpartTmplt& operator=(const ClausenFFTpartTmplt& x)=delete;


  public: // ---- Access -------------------------------------------------------------------------------------


    void add(const ClausenFFTpartTmplt& sub){
      blocks.push_back(new ClausenFFTblockTmplt(d,m,sub.index));
      d+=sub.d;
      m+=sub.m;
    }


  public: // ---- Fourier tranforms --------------------------------------------------------------------------


    SnPart uptransform(const SnVec& v) const{
      SnPart P(irrep,m,cnine::fill::zero);
      for(auto p:blocks){
	ClausenFFTblockTmplt& b=*p;
	P.add_to_block(b.ioffs,b.joffs,*v.parts[b.subix]);
      }
      //cout<<P<<endl;
      return P;
    }

    /*
    SnPart downtransform(const SnVec& v) const{
      SnPart P(irrep,m,cnine::fill::zero);
      
      for(auto p:blocks){
	ClausenFFTblockTmplt& b=*p;
	P.add_to_block(b.ioffs,b.joffs,*v.parts[b.subix]);
      }
      return P;
    }
    */


  public: // ---- I/O ----------------------------------------------------------------------------------------


    string str(const string indent="") const{
      ostringstream oss;
      oss<<indent<<"Part "<<index<<" "<<irrep->lambda.str()<<" ";
      oss<<"("<<d<<","<<m<<") ";
      oss<<""<<endl; //" ("<<index<<")"<<endl;
      for(int i=0; i<blocks.size(); i++){
	oss<<blocks[i]->str(indent+"  ");
      }
      return oss.str();
    }

    friend ostream& operator<<(ostream& stream, const ClausenFFTpartTmplt& x){
      stream<<x.str(); return stream;
    }

  };

}

#endif
