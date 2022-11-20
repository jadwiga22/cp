void Propagate(int x, int len){
	if(x>=B) return;
	int l=(x<<1), r=l+1;
	L[l]+=L[x];
	M[l]+=L[x];
	S[l]+=(1LL*L[x]*(len>>1));
	L[r]+=L[x];
	M[r]+=L[x];
	S[r]+=(1LL*L[x]*(len>>1));
	L[x]=0;
	M[x]=min(M[l],M[r]);
	S[x]=S[l]+S[r];
}

ll Sum(int x, int be, int en, int a, int b){
	Propagate(x,en-be+1);
	if(be==a && en==b){
		return S[x];
	}
	int mid=((be+en)>>1), l=(x<<1), r=l+1;
	ll res=0;
	if(a<=mid) res+=Sum(l,be,mid,a,min(b,mid));
	if(b>mid) res+=Sum(r,mid+1,en,max(a,mid+1),b);
	Propagate(x,en-be+1);
	return res;
}

ll Min(int x, int be, int en, int a, int b){
	Propagate(x,en-be+1);
	if(be==a && en==b){
		return M[x];
	}
	int mid=((be+en)>>1), l=(x<<1), r=l+1;
	ll res=INF;
	if(a<=mid) res=min(res, Min(l,be,mid,a,min(b,mid)));
	if(b>mid) res=min(res,Min(r,mid+1,en,max(a,mid+1),b));
	Propagate(x,en-be+1);
	return res;
}

void Add(int x, int be, int en, int a, int b, int val){
	Propagate(x,en-be+1);
	if(be==a && en==b){
		M[x]+=val;
		L[x]+=val;
		S[x]+=(1LL*val*(en-be+1));
		return;
	}
	int mid=((be+en)>>1), l=(x<<1), r=l+1;
	if(a<=mid) Add(l,be,mid,a,min(b,mid),val);
	if(b>mid) Add(r,mid+1,en,max(a,mid+1),b,val);
	Propagate(x,en-be+1);
}
