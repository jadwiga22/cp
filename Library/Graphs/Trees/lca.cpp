int anc[LOG][MAXN];
int depth[MAXN];
bool vis[MAXN];
vi G[MAXN];

void DFS(int v){
	vis[v]=true;
	for(int u : G[v]){
		if(!vis[u]){
			depth[u]=depth[v]+1;
			anc[0][u]=v;
			DFS(u);
		}
	}
}

void Prepare(int n){
	anc[1][1]=1;
	DFS(1);
	FOR(j,1,LOG){
		FOR(i,1,n+1){
			anc[j][i]=anc[j-1][anc[j-1][i]];
		}
	}
}

int LCA(int a, int b){
	if(depth[b]<depth[a]){
		swap(a,b);
	}
	FORD(i,LOG-1,-1){
		if(depth[anc[i][b]]>=depth[a]) b=anc[i][b];
	}
	FORD(i,LOG-1,-1){
		if(anc[i][a]!=anc[i][b]){
			a=anc[i][a];
			b=anc[i][b];
		}
	}
	if(a==b) return a;
	return anc[0][a];
}
