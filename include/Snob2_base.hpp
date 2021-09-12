#ifndef _Snob2_base
#define _Snob2_base

#include "Cnine_base.hpp"

using namespace std; 
//using namespace Cnine; 


#define SNOB2_ASSERT(condition, message) if (!(condition)) {cout<<message<<endl; assert ((condition)); exit(-1); }

#define SNOB2_UNIMPL() printf("Snob2 error: function \"%s\" not implemented.\n",__PRETTY_FUNCTION__);

#define SNOB2_ERROR(cmd) {CoutLock lk; cerr<<"Snob2 error in function '"<<__PRETTY_FUNCTION__<<"' : "<<cmd<<endl;} exit(1);



namespace Snob2{

  inline ostream& operator<<(ostream& stream, const vector<int>& v){
    stream<<"(";
    for(int i=0; i<v.size()-1; i++)
      stream<<v[i]<<",";
    if(v.size()>0) stream<<v[v.size()-1]<<")";
    return stream;
  }


}






#endif 
