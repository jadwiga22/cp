vii G[MAXN];
queue<int> Q;
bool onQueue[MAXN];
bool reachable[MAXN];
ll dist[MAXN];
int len[MAXN];

bool SPFA(int s, int n){ // false if negative cycle
	FOR(i,0,n+1) dist[i]=INF;
	dist[s]=0;
	Q.push(s);
	onQueue[s]=true;
	while(!Q.empty()){
		int v=Q.front();
		Q.pop();
		onQueue[v]=false;
		FOR(i,0,n+1){
			for(pii e : G[i]){
				if(dist[i]+e.nd<dist[e.st]){
					dist[e.st]=dist[i]+e.nd;
					len[e.st]=len[i]+1;
					if(len[e.st]==n) return false;
					if(!onQueue[e.st]) Q.push(e.st);
				}
			}
			
		}
	}
	return true;
}

void DFS(int v){
	reachable[v]=true;
	for(pii u : G[v]){
		if(!reachable[u.st]) DFS(u.st);
	}
}
