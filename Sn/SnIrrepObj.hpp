#ifndef _SnIrrepObj
#define _SnIrrepObj

#include "IntegerPartition.hpp"
#include "ContiguousCycle.hpp"
#include "RtensorObj.hpp"


namespace Snob2{

  typedef cnine::RtensorObj rtensor;
  //typedef cnine::CtensorObj ctensor;


  class SnIrrepObj{
  public:

    int n;
    int d;
    IntegerPartition lambda;
    vector<YoungTableau*> tableaux;
    vector<SnIrrepObj*> ancestors;
    vector<SnIrrepObj*> descendents;

    mutable int* YORt=nullptr;
    mutable double* YOR1;
    mutable double* YOR2;


  public:

    SnIrrepObj(const IntegerPartition& _lambda):
      lambda(_lambda){
      tableaux=_combibank->get_YoungTableaux(lambda);
      d=tableaux.size();
      n=_lambda.getn();
    }

    ~SnIrrepObj(){
      delete[] YORt;
      delete[] YOR1;
      delete[] YOR2;
    }


  public:

    SnIrrepObj(const SnIrrepObj& x)=delete;

    SnIrrepObj& operator=(const SnIrrepObj& x)=delete;


  public: // ---- Access ------------------------------------------------------------------------------------ 

    
    int index(const YoungTableau& t) const {
      int i=0; for(auto p: tableaux) if(*p==t) return i; else i++; return -1;}


  public: // ---- Operations --------------------------------------------------------------------------------


    rtensor operator()(const SnElement& sigma) const{
      rtensor R(cnine::dims(d,d),cnine::fill::identity);
      apply_left(R,sigma);
      return R;
    }

  public: // ---- Ancestors ---------------------------------------------------------------------------------




  public: // ---- apply_left to whole matrix ----------------------------------------------------------------


    void apply_left(rtensor& A, const SnElement sigma) const{
      SNOB2_ASSERT(sigma.getn()==n,"Permutation wrong size");
      vector<int> shifts(n);
      for(int i=n; i>0; i--){
	int a=sigma(i);
	shifts[i-1]=a;
	for(int j=1; j<i; j++) if(sigma.p[j-1]>a) sigma.p[j-1]--;
      }
      for(int i=2; i<=n; i++){
	//cout<<i<<" "<<shifts[i-1]<<endl;
	//cout<<A<<endl;
	for(int a=i-1; a>=shifts[i-1]; a--)
	  apply_left(A,a);
      }
    }

    void apply_left(rtensor& A, const ContiguousCycle& cyc) const{
      for(int i=cyc.b-1; i>=cyc.a; i--)
	apply_left(A,i);
    }

    void apply_left(rtensor& A, const int tau) const{
      SNOB2_ASSERT(A.get_dim(0)==d,"Matrix wrong size");
      const int J=A.get_dim(1);
      computeYOR();
      bool done[d];
      //cout<<"---"<<lambda<<endl<<endl;
      for(int i=0; i<d; i++) done[i]=false;
      for(int i=0; i<d; i++){
	if(done[i]) continue; 
	double c1,c2;
	const int i2=YOR(tau,i,c1,c2);
	if(i2==-1){
	  //cout<<"c1="<<c1<<endl;
	  for(int j=0; j<J; j++)
	    A.set_value(i,j,c1*A.get_value(i,j));
	}else{
	  //cout<<"c1="<<c1<<" c2="<<c2<<endl;
	  for(int j=0; j<J; j++){
	    float t=A.get_value(i,j);
	    A.set_value(i,j,c1*t+c2*A.get_value(i2,j));
	    A.set_value(i2,j,-c1*A.get_value(i2,j)+c2*t);
	    done[i2]=true;
	  }
	}
      }
    }


  public: // ---- apply_left to block ------------------------------------------------------------------------


    void apply_left(rtensor& A, const SnElement sigma, int beg, int end) const{
      SNOB2_ASSERT(sigma.getn()==n,"Permutation wrong size");
      vector<int> shifts(n);
      for(int i=n; i>0; i--){
	int a=sigma(i);
	shifts[i-1]=a;
	for(int j=1; j<i; j++) if(sigma.p[j-1]>a) sigma.p[j-1]--;
      }
      for(int i=2; i<=n; i++){
	//cout<<i<<" "<<shifts[i-1]<<endl;
	//cout<<A<<endl;
	for(int a=i-1; a>=shifts[i-1]; a--)
	  apply_left(A,a,beg,end);
      }
    }

    void apply_left(rtensor& A, const ContiguousCycle& cyc, const int beg, const int end) const{
      for(int i=cyc.b-1; i>=cyc.a; i--)
	apply_left(A,i,beg,end);
    }

    void apply_left(rtensor& A, const int tau, int beg, int end) const{
      SNOB2_ASSERT(A.get_dim(0)==d,"Matrix wrong size");
      //const int J=A.get_dim(1);
      computeYOR();
      bool done[d];
      for(int i=0; i<d; i++) done[i]=false;
      for(int i=0; i<d; i++){
	if(done[i]) continue; 
	double c1,c2;
	const int i2=YOR(tau,i,c1,c2);
	if(i2==-1){
	  for(int j=beg; j<end; j++)
	    A.set_value(i,j,c1*A.get_value(i,j));
	}else{
	  for(int j=beg; j<end; j++){
	    float t=A.get_value(i,j);
	    A.set_value(i,j,c1*t+c2*A.get_value(i2,j));
	    A.set_value(i2,j,-c1*A.get_value(i2,j)+c2*t);
	    done[i2]=true;
	  }
	}
      }
    }


  public: // ---- apply_left to multiple blocks --------------------------------------------------------------


    void apply_left(rtensor& A, const SnElement sigma, const int beg, const int end, const int stride) const{
      SNOB2_ASSERT(sigma.getn()==n,"Permutation wrong size");
      vector<int> shifts(n);
      for(int i=n; i>0; i--){
	int a=sigma(i);
	shifts[i-1]=a;
	for(int j=1; j<i; j++) if(sigma.p[j-1]>a) sigma.p[j-1]--;
      }
      for(int i=2; i<=n; i++){
	apply_left(A,ContiguousCycle(shifts[i-1],i),beg,end,stride);
      }
    }

    void apply_left(rtensor& A, const ContiguousCycle& cyc, const int beg, const int end, const int stride) const{
      for(int j=0; j<A.dim(1)/stride; j++)
	for(int i=cyc.b-1; i>=cyc.a; i--)
	  apply_left(A,i,beg+j*stride,end+j*stride);
    }


  private: // ---- YOR ---------------------------------------------------------------------------------------

    
    int YOR(const int tau, const int t, double& c1, double& c2) const {
      int index=t*(n-1)+tau-1; c1=YOR1[index]; c2=YOR2[index]; return YORt[index];
    }
  
    void computeYOR() const{
      if (YORt) return;
      //cout<<"Computing YOR for "<<lambda<<endl;
      YORt=new int[d*(n-1)];
      YOR1=new double[d*(n-1)];
      YOR2=new double[d*(n-1)];
      for(int i=0; i<d; i++){ // for each tableau...
	for(int tau=1; tau<n; tau++){ // for each transposition (tau,tau+1)...
	  const int ix=i*(n-1)+tau-1;
	  YoungTableau tableau(*tableaux[i]);
	  int delta=tableau.apply_transp(tau);
	  if((delta==1)||(delta==-1)){
	    YORt[ix]=-1; YOR1[ix]=delta; YOR2[ix]=0;
	  }else{
	    YORt[ix]=index(tableau);
	    //cout<<shape<<" "<<i<<" "<<tau<<" "<<YORt[index]<<endl;
	    YOR1[ix]=1.0/delta;
	    YOR2[ix]=sqrt(1-1.0/(delta*delta));
	  }
	}
      }

    }


  public:

    string str(const string indent="") const{
      return "SnIrrepObj("+lambda.str()+")";
    }

    friend ostream& operator<<(ostream& stream, const SnIrrepObj& x){
      stream<<x.str(); return stream;
    }

  };

}

#endif
