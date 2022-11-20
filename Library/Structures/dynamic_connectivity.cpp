int rep[MAXN];
int ran[MAXN];
pii Ed[MAXN];
int Num=0;
map<pii,int> M;
vi T[(B<<1)];
pii bef[2][MAXN];
int nu[MAXN];
int Res[B];
bool ask[MAXN];

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
	Num--;
	if(ran[x]>ran[y]) swap(x,y);
	rep[x]=y;
	ran[y]+=ran[x];
}

inline void SingleAdd(int a){
	int y=Find(Ed[a].st), z=Find(Ed[a].nd);
	bef[0][a]={y,ran[y]};
	bef[1][a]={z,ran[z]};
	nu[a]=Num;
	Union(Ed[a].st,Ed[a].nd);
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
	
	Num=nu[a];	
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

void DFS(int v){
	AddEdges(v);
	if(v>=B){
		Res[v-B]=Num;
	}
	else{
		DFS((v<<1));
		DFS((v<<1)+1);
	}
	RemoveEdges(v);
}



int main(){    
	int n,k;
	scanfast(&n);
	scanfast(&k);
	
	Num=n;
	
	FOR(i,0,k){
		char c;
		scanfastC(&c);
		if(c=='?'){
			ask[i]=true;
		}
		else{
			scanfast(&Ed[i].st);
			scanfast(&Ed[i].nd);
			if(Ed[i].st<Ed[i].nd) swap(Ed[i].st,Ed[i].nd);
			if(c=='+') M.insert({Ed[i],i});
			else{
				Add(M[Ed[i]],i,i);
				M.erase(Ed[i]);
			}
		}
		
	}
	
	for(auto m : M){
		Add(m.nd,k,m.nd);
	}
	
	Prepare(n);	
	DFS(1);
	
	FOR(i,0,k){
		if(ask[i]) printf("%d\n", Res[i]);
	}
	
	
	return 0;
}
