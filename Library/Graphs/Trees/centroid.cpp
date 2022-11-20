vi G[MAXN];
bool blocked[MAXN];
int subt[MAXN];
int dist[MAXN];
int red[MAXN];
vii Cen[MAXN];
int z=0,o=1;

void CalcSubt(int& v, int& f){
	for(int u : G[v]){
		if(u!=f){
			CalcSubt(u,v);
			subt[v]+=subt[u];
		}
	}
	subt[v]++;
}

int Centroid(int& v){
	for(int u : G[v]){
		if(!blocked[u] && subt[u]>(subt[v]>>1)){
			swap(subt[u],subt[v]);
			subt[v]=subt[u]-subt[v];
			return Centroid(u);
		}
	}
	return v;
}

void DFS(int& v, int& f, int& C){
	Cen[v].pb({C,dist[v]});
	for(int u : G[v]){
		if(!blocked[u] && u!=f){
			dist[u]=dist[v]+1;
			DFS(u,v,C);
		}
	}
}

void Decomp(int& v){
	int C=Centroid(v);
	blocked[C]=true;
	dist[C]=0;
	DFS(C,z,C);
	for(int u : G[C]){
		if(!blocked[u]) Decomp(u);
	}
}

inline void Paint(int& v){
	for(pii c : Cen[v]){
		red[c.st]=min(red[c.st], c.nd);
	}
}

inline int MinDist(int& v){
	int res=INF;
	for(pii c : Cen[v]){
		res=min(res,c.nd+red[c.st]);
	}
	return res;
}


int main(){
	int n,m;
	scanfast(&n);
	scanfast(&m);
	
	FOR(i,1,n){
		int a,b;
		scanfast(&a);
		scanfast(&b);
		G[a].pb(b);
		G[b].pb(a);
	}
	CalcSubt(o,z);
	Decomp(o);
	
	FOR(i,1,n+1) red[i]=INF;
	Paint(o);
	
	FOR(i,0,m){
		int x,v;
		scanfast(&x);
		scanfast(&v);
		if(x==1) Paint(v);
		else printf("%d\n", MinDist(v));
	}
	
	return 0;
}
