int rep[MAXN];
int ran[MAXN];
pii Ed[MAXN];
int l[MAXN];
int Bad=0,A=0,ind_e=0;
pii E[MAXN];
vi T[(B<<1)];
pii bef[2][MAXN];
int ba[MAXN];
int Res[MAXN];
int V[MAXN];

inline void Prepare(int n){
	FOR(i,1,n+1){
		rep[i]=i;
		ran[i]=1;
	}
}

inline int Find(int x){
	if(rep[x]!=x){
		return Find(rep[x]);
	} 
	return rep[x];
}

inline void Union(int a, int b){
	int x=Find(a), y=Find(b);
	if(x==y) return;
	if(ran[x]&1 && ran[y]&1) Bad-=2;
	if(ran[x]>ran[y]) swap(x,y);
	rep[x]=y;
	ran[y]+=ran[x];
}

inline void SingleAdd(int a){
	int y=Find(Ed[a].st), z=Find(Ed[a].nd);
	bef[0][a]={y,ran[y]};
	bef[1][a]={z,ran[z]};
	ba[a]=Bad;
	Union(Ed[a].st,Ed[a].nd);
	A=max(A,l[a]);
}

inline void AddEdges(int x){
	for(int a : T[x]){
		SingleAdd(a);
	}
}

inline void SingleRemove(int a){
	rep[bef[0][a].st]=bef[0][a].st;
	ran[bef[0][a].st]=bef[0][a].nd;
	
	rep[bef[1][a].st]=bef[1][a].st;
	ran[bef[1][a].st]=bef[1][a].nd;
	
	Bad=ba[a];	
}

inline void RemoveEdges(int x){
	FORD(i,(int)T[x].size()-1,-1){
		SingleRemove(T[x][i]);
	}
}

inline void Add(int a, int b, int e){
	a+=B, b+=B;
	while(a<b){
		if(a&1){
			T[a].pb(e);
			a++;
		}
		if(!(b&1)){
			T[b].pb(e);
			b--;
		}
		a>>=1;
		b>>=1;
	}
	if(a==b) T[a].pb(e);
}

void DFS(int v, int m){
	AddEdges(v);
	if(v>=B){
		if(v-B<m){
			int ind=0;
			while(Bad){
				while(ind_e<m && E[ind_e].nd>v-B){
					ind_e++;
				}
				if(ind_e>=m) break;
				SingleAdd(E[ind_e].nd);
				V[ind++]=E[ind_e].nd;
				ind_e++;
			}
			
			if(!Bad) Res[v-B]=A;
			else Res[v-B]=-1;
			FORD(i,ind-1,-1){
				SingleRemove(V[i]);
				Add(V[i],v-B-1,V[i]);
			}			
		}
	}
	else{
		DFS((v<<1)+1,m);
		DFS((v<<1),m);
	}
	RemoveEdges(v);
}



int main(){
	int n,m;
	scanfast(&n);
	scanfast(&m);
	
	Bad=n;
	
	FOR(i,0,m){
		scanfast(&Ed[i].st);
		scanfast(&Ed[i].nd);
		scanfast(&l[i]);
		E[i]={l[i],i};
	}
	
	sort(E,E+m);
	
	Prepare(n);	
	DFS(1,m);
	
	FOR(i,0,m){
		printf("%d\n", Res[i]);
	}
	
	
	return 0;
}
