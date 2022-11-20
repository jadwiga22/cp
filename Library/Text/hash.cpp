int H[MAXN];
int Pot[MAXN];
int Rev[MAXN];

int Pow(int x, int n){
	if(!n) return 1;
	int tmp=Pow(x,(n>>1));
	tmp=(1LL*tmp*tmp)%MOD;
	if((n&1)) tmp=(1LL*x*tmp)%MOD;
	return tmp;
}


int Hash(int i, int j){
	return (1LL*(H[j]-H[i-1]+MOD)*Rev[i])%MOD;
}


void Prepare(int& n){
	Pot[0]=1;
	FOR(i,1,MAXN){
		Pot[i]=(1LL*Pot[i-1]*P)%MOD;
	}
	Rev[MAXN-1]=Pow(Pot[MAXN-1],MOD-2);
	FORD(i,MAXN-2,-1){
		Rev[i]=(1LL*Rev[i+1]*P)%MOD;
	}
	scanfast(&n);
	FOR(i,1,n+1){
		scanfastC(&T[i]);
		H[i]=(1LL*Pot[i]*(T[i]-'a')+H[i-1])%MOD;
	}
}
