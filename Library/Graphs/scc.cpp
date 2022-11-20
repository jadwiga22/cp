vi G[MAXN];
vi revG[MAXN];
vi SCC[MAXN];
stack<int> S;

int deg[MAXN];
int SCCnum[MAXN];
int reachable[MAXN];
bool vis[MAXN];
bool DAGvis[MAXN];
bool onStack[MAXN];
int cnt[MAXN];


inline void DFS(int v){
	onStack[v]=true;
	
	for(auto u : G[v]){
		if(!onStack[u]){
			DFS(u);
		}
	}
	
	S.push(v);
}

inline void revDFS(int v){
	vis[v]=true;
	cnt[SCCnum[v]]++;
	for(auto u : revG[v]){
		if(!vis[u]){
			SCCnum[u]=SCCnum[v];
			revDFS(u);
		}
		else if(SCCnum[u]!=SCCnum[v]){
			SCC[SCCnum[v]].pb(SCCnum[u]);
			deg[SCCnum[u]]++;
		}
	}
}

inline void FindSCC(int n){
	int num=1;
	FOR(i,1,n+1){
		if(!onStack[i]) DFS(i);
	}
	while(!S.empty()){
		int v=S.top();
		S.pop();
		if(SCCnum[v]) continue;
		SCCnum[v]=num++;
		revDFS(v);
	}
}

inline void DFS_DAG(int v){
	DAGvis[v]=true;
	for(auto u : SCC[v]){
		deg[u]--;
		reachable[u]+=(reachable[v]+cnt[v]);
		if(!deg[u]) DFS_DAG(u);
	}
}

inline void FindReachable(int n){
	FOR(i,1,n+1){
		if(!deg[i] && !DAGvis[i]) DFS_DAG(i);
	}
}

inline void PrintReachable(int n){
	FOR(i,1,n+1){
		printf("%d\n", reachable[SCCnum[i]]+cnt[SCCnum[i]]-1);
	}
}

