vi G[MAXN];
int dist[MAXN];
bool vis[MAXN];

void DFS(int v){
	vis[v]=true;
	for(int u : G[v]){
		if(!vis[u]){
			dist[u]=dist[v]+1;
			DFS(u);
		}
	}
}

int Diameter(int n){
	FOR(i,1,n+1){
		vis[i]=false;
	}
	dist[1]=0;
	DFS(1);
	int v=1,res=0;
	FOR(i,1,n+1){
		vis[i]=false;
		if(dist[i]>dist[v]) v=i;
	}
	dist[v]=0;
	DFS(v);
	FOR(i,1,n+1) res=max(res,dist[i]);
	return res;
}
