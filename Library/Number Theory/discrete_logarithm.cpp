unordered_map<int,int> M;

int Sqrt(int n){
	int d=1,g=n;
	while(d+1<g){
		int s=((d+g)>>1);
		if(1LL*s*s<=n) d=s;
		else g=s;
	}
	return d;
}

int Pow(int x, int n, int p){
	if(!n) return 1;
	int res=Pow(x,(n>>1),p);
	res=(1LL*res*res)%p;
	if(n&1) res=(1LL*res*x)%p;
	return res;
}

int DiscLog(int a, int b, int p){ //(a^res)%p=b
	a%=p, b%=p;
	if((bool)a ^ (bool)b) return -1;
	if(!a && !b) return 1;
	int root=Sqrt(p), cur=(1LL*Pow(Pow(a,p-2,p),root-1,p)*b)%p;
	M.insert({cur,root-1});
	FORD(i,root-2,-1){
		cur=(1LL*cur*a)%p;
		if(M.count(cur)) M[cur]=i;
		else M.insert({cur,i});
	}
	int tmp=Pow(a,root,p);
	cur=1;
	
	FOR(i,0,root+1){
		if(M.count(cur)) return i*root+M[cur];
		cur=(1LL*cur*tmp)%p;
	}
	return -1;
}
