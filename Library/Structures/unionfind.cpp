void Prepare(int n){
	FOR(i,1,n+1){
		rep[i]=i;
		ran[i]=1;
	}
}

int Find(int x){
	if(rep[x]!=x){
		rep[x]=Find(rep[x]);
	} 
	return rep[x];
}

void Union(int a, int b){
	int x=Find(a), y=Find(b);
	if(ran[x]<ran[y]) swap(x,y);
	rep[y]=x;
	ran[x]+=ran[y];
}
