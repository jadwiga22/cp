void ToBin(ll a){
	FORD(i,LEN-1,-1){
		Cur[i]=(a&1);
		a>>=1;
	}
}

void Insert(ll a){
	ToBin(a);
	int j=0;
	FOR(i,0,LEN){
		if(T[j][Cur[i]]) j=T[j][Cur[i]];
		else{
			T[j][Cur[i]]=++ind;
			j=ind;
		}
	}
	
}

ll Xor(int l, int r, int d){
	if(d<0) return 0;
	ll res=0;
	bool flag=false;
	if(T[l][0] && T[r][1]){
		res=max(res,(1LL<<d)+Xor(T[l][0],T[r][1],d-1));
		flag=true;
	}
	if(T[l][1] && T[r][0]){
		res=max(res,(1LL<<d)+Xor(T[l][1],T[r][0],d-1));
		flag=true;
		
	}
	if(flag) return res;
	if(T[l][0]){
		res=max(res,Xor(T[l][0],T[r][0],d-1));
	}
	else{
		res=max(res,Xor(T[l][1],T[r][1],d-1));
	}
	return res;

}
