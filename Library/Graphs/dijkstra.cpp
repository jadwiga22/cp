vector<pii> G[MAXN];
int dist[MAXN];

void Dijkstra(int v, int n){
	priority_queue<pii> Q;
	FOR(i,1,n+1) dist[i]=INF;
	dist[v]=0;	
	Q.push({0,v});
	while(!Q.empty()){
		pii best=Q.top();
		Q.pop();
		for(pii u : G[best.nd]){
			if(dist[best.nd]+u.nd<dist[u.st]){
				dist[u.st]=dist[best.nd]+u.nd;
				Q.push({-dist[u.st], u.st});
			}
		}
	}
}
