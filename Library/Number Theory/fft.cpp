typedef complex<double> cmpl;
const int MAXN=(1<<17);

int R[MAXN];
int Ord[MAXN];
cmpl Roots[2][MAXN];

inline void Prepare(int& n){
	cmpl w0=-1, w1=-1;
	int cn=2, k=(n>>1);
	while(cn<n){
		w0=sqrt(w0);
		cn<<=1;
	}
	w1=pow(w0,-1);
	Roots[0][0]=Roots[1][0]=1;
	FOR(i,1,k){
		Roots[0][i]=Roots[0][i-1]*w0;
		Roots[1][i]=Roots[1][i-1]*w1;
	}
	int cur=1;
	Ord[0]=0;
	while(cur<n){
		FOR(j,0,cur){
			Ord[j+cur]=Ord[j]+k;
		}
		cur<<=1, k>>=1;
	}
}

inline vector<cmpl> FFT(int& n, vector<cmpl>& A, bool sign){
	vector<cmpl> W;
	W.resize(n);
	
	FOR(i,0,n) W[i]=A[Ord[i]];
	
	int k=2, s=(n>>1);
	while(k<=n){
		int c=(k>>1);
		for(int i=0; i<n; i+=k){
			int lim=i+c, ind=0;
			FOR(j,i,lim){
				cmpl x=W[j], y=Roots[sign][ind]*W[j+c];
				W[j]=x+y;
				W[j+c]=x-y;
				ind+=s;
			}
		}
		k<<=1, s>>=1;
	}
	if(sign){
		FOR(i,0,n){
			W[i]/=n;
		}
	}
	return W;
}

int main(){
	string a,b;
	scanfastS(&a);
	scanfastS(&b);
	
	int n=max(sz(a), sz(b)),p=1;
	while(p<n) p<<=1;
	n=p<<1;
	vector<cmpl> A, B;
	A.resize(n,0), B.resize(n,0);
	
	FOR(i,0,sz(a)){
		A[sz(a)-i-1]=a[i]-'0';
	}
	
	FOR(i,0,sz(b)){
		B[sz(b)-i-1]=b[i]-'0';
	}
	
	Prepare(n);
	
	vector<cmpl> VA=FFT(n,A,0), VB=FFT(n,B,0);
	FOR(i,0,n){
		VA[i]*=VB[i];
	}
	vector<cmpl> V=FFT(n,VA,1);
	
	int buff=0;
	for(int i=0; i<n; i++){
		int x=round(V[i].real());
		R[i]=(x+buff)%10;
		buff=(x+buff)/10;
	}
	
	int ind=n-1;
	while(ind>=0 && !R[ind]) ind--;
	if(ind<0){
		printf("0");
		return 0;
	}
	
	FORD(j,ind,-1){
		printf("%d", R[j]);
	}
	
	return 0;
}
