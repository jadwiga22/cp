vii G[MAXN];
ll dist[MAXN];
bool reachable[MAXN];

bool isCycle(int n){
	FOR(x,0,n){
		for(pii u : G[x]){
			if(dist[x]+u.nd<dist[u.st]) return true;
		}
	}
	return false;
}

void DFS(int v){
	reachable[v]=true;
	for(pii u : G[v]){
		if(!reachable[u.st]) DFS(u.st);
	}
}

void BelFor(int s, int n){
	FOR(i,0,n){
		dist[i]=INF;
	}
	dist[s]=0;
	queue<int> Q;
	FOR(i,0,n-1){
		FOR(j,0,n){
			for(pii u : G[j]){
				dist[u.st]=min(dist[u.st],dist[j]+1LL*u.nd);
			}
		} 
	}
	if(isCycle(n)) printf("NIE");
	else{
		DFS(s);
		FOR(i,0,n){
			if(i==s || !reachable[i]) continue;
			printf("%d %lld\n", i,dist[i]);
		}
	}
}
