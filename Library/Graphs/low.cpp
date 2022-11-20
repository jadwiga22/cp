vi G[MAXN];
int pre[MAXN];
int low[MAXN];

void DFS(int v, int f, int& t){
	low[v]=pre[v]=t++;
	for(int u : G[v]){
		if(u==f) continue; //uwaga na krawedzie wielokrotne!!!
		if(!pre[u]){
			DFS(u,v,t);
			low[v]=min(low[v],low[u]);
		}
		else low[v]=min(low[v],pre[u]);
	}
}

// father - son is a bridge iff low[son]>=pre[son] (in fact, low[son]==pre[son])
// v is an articulation point if
//	- is a root and has more than 1 son
//	- is not a root and for at least one son s low[s]>=pre[v]
