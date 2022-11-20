vi G[MAXN];
vi revG[MAXN];
int deg[MAXN];
int nr[MAXN];
int T[MAXN];
int ind=1;

void DFSTop(int v){ // v jest przed u jesli jest krawedz v->u
	T[ind]=v;
	nr[v]=ind++;
	
	for(int u : G[v]){
		deg[u]++;
		if((int)revG[u].size()==deg[u]) DFSTop(u);
	}
}

void TopoSort(int n){
	FOR(i,1,n+1){
		if(!revG[i].size()) DFSTop(i);
	}
}
