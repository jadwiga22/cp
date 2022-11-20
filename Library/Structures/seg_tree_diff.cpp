inline void Actualize(int& x){
	T[x]=Ad[x]+min(T[(x<<1)],T[(x<<1)+1]);
}

inline void Add(int a, int b, ll val){
	a+=B, b+=B;
	T[a]+=val, Ad[a]+=val;
	if(a!=b){Ad[b]+=val; T[b]+=val;}
	while(a>1){
		if((a>>1)!=(b>>1)){
			if(!(a&1)){
				T[a+1]+=val;
				Ad[a+1]+=val;
			} 
			if(b&1){
				T[b-1]+=val;
				Ad[b-1]+=val;
			} 
		}
		a>>=1;
		b>>=1;
		Actualize(a), Actualize(b);
	}
}

