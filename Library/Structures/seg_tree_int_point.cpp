int Val(int pos){
	pos+=B;
	int res=0;
	while(pos){
		res+=T[pos];
		pos>>=1;
	}
	return res;
}

void Change(int a, int b, int val){
	a+=B;
	b+=B;
	int res=0;
	while(a<b){
		if((a&1)){
			T[a]+=val;
			a++;
		}
		if(!(b&1)){
			T[b]+=val;
			b--;
		}
		a>>=1;
		b>>=1;
	}
	if(a==b) T[a]+=val
	return res;
}
