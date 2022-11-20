vi LG[MAXN];
vi RG[MAXN];
int Lmatch[MAXN];
int Rmatch[MAXN];
int dist[MAXN];

bool BFS(int n){
	queue<int> Q;
	FOR(i,0,n+1) dist[i]=INF;
	FOR(i,1,n+1){
		if(!Lmatch[i]){
			Q.push(i);
			dist[i]=0;
		} 
	}
	while(!Q.empty()){
		int naj=Q.front();
		Q.pop();
		for(int u : LG[naj]){
			if(dist[Rmatch[u]]>dist[naj]+1){
				dist[Rmatch[u]]=dist[naj]+1;
				Q.push(Rmatch[u]);
			}
		}
	}
	return dist[0]!=INF;
}

bool DFS(int v){
	if(!v) return true;
	for(int u : LG[v]){
		int w=Rmatch[u];
		if(dist[w]==dist[v]+1 && DFS(w)){
			Lmatch[v]=u;
			Rmatch[u]=v;
			return true;
		}
	}
	dist[v]=INF;
	return false;
}

int Match(int n){
	while(BFS(n)){
		FOR(i,1,n+1){
			if(!dist[i]) DFS(i);
		}
	}
	int res=0;
	FOR(i,1,n+1) if(Lmatch[i]) res++;
	return res;
}
