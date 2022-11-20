int n,m;
vi G[MAXM*2];
bool vis[MAXM*2];
int parent[MAXM*2];
int ed[MAXM*2];
int T[MAXN][MAXN];
int ind=0;

struct edge{
	int f,cap,a,b;
};

vector<edge> E;

void AddEdge(int a, int b, int c){
	edge e1={c,c,a,b}, e2={0,0,b,a};
	G[a].pb(E.size());
	E.pb(e1);
	G[b].pb(E.size());
	E.pb(e2);
}

bool BFS(int s){
	queue<int> Q;
	vis[s]=true;
	Q.push(s);
	while(!Q.empty()){
		int v=Q.front();
		Q.pop();
		for(int id : G[v]){
			if(!vis[E[id].b] && E[id].f>0){
				vis[E[id].b]=true;
				ed[E[id].b]=id;
				parent[E[id].b]=v;
				Q.push(E[id].b);
				if(E[id].b==1) return true;
			}
		}
	}
	return false;
}

int MinPath(int s, int t){
	int x=t+1, res=INF;
	while(x!=s){
		res=min(E[ed[x]].f,res);
		x=parent[x];
	}
	return res;
}

void Actualize(int s, int t, int c){
	int x=t+1;
	while(x!=s){
		E[ed[x]].f-=c;
		E[ed[x]^1].f+=c;
		x=parent[x];
	}
}

int MaxFlow(int s, int t){
	int res=0;
	while(BFS(s)){
		int c=MinPath(s,t);
		res+=c;
		Actualize(s,t,c);
		for(edge e : E) vis[e.a]=vis[e.b]=false;
	}
	return res;
}
