void Change(int pos, int val){
	pos+=B;
	T[pos]=val;
	while(pos>1){
		pos>>=1;
		int l=(pos<<1), r=l+1;
		T[pos]=max(T[l],T[r]);
	}
}

int Max(int a, int b){
	a+=B;
	b+=B;
	int res=0;
	while(a<b){
		if((a&1)){
			res=max(res,T[a]);
			a++;
		}
		if(!(b&1)){
			res=max(res,T[b]);
			b--;
		}
		a>>=1;
		b>>=1;
	}
	if(a==b) res=max(res,T[a]);
	return res;
}
