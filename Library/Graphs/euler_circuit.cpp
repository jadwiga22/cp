//semi-Eulerian iff zero or two veritces have odd degree

bool vis[MAXM];
bool visV[MAXN];
vii G[MAXN];
stack<int> S;
int last[MAXN];
int deg[MAXN];

inline bool Isolated(int v){
	while(last[v]<G[v].size() && vis[G[v][last[v]].nd]) last[v]++;
	return last[v]>=G[v].size();
}


inline void NewCycle(int v){
	while(!Isolated(v)){
		S.push(v);
		vis[G[v][last[v]].nd]=true;
		last[v]++;
		v=G[v][last[v]-1].st;
	}
}

inline void FindCircuit(int n){
	int st=0;
	FOR(i,1,n+1){
		if(!deg[i]) continue;
		if(!st){
			st=i;
			break;
		}
	}
	if(!st) return;
	S.push(st);
	while(!S.empty()){
		int v=S.top();
		S.pop();
		NewCycle(v);
		printf("%d ",v);
	}
}



inline void Mark(int v){
    visV[v]=true;
    for(pii u : G[v]){
    	if(!visV[u.st]){
    		Mark(u.st);
    	}
    }
}

bool Eulerian(int n, int& st){
	int ind=1;
	while(ind<=n && !deg[ind]) ind++;
	if(ind>n) return true;
	st=ind;
	Mark(st);
	FOR(i,1,n+1){
		if((deg[i]&1) || (!visV[i] && deg[i])) return false;
	}
	return true;
}

void Clear(int n,int m){
	FOR(i,1,n+1){
		G[i].resize(0);
		last[i]=deg[i]=0;
		visV[i]=false;
	}
	FOR(i,0,m) vis[i]=false;
}


int main(){
   	int t;
   	scanfast(&t);
	
	FOR(i,0,t){
		int n,m;
		scanfast(&n);
		scanfast(&m);
		FOR(j,0,m){
			int a,b;
			scanfast(&a);
			scanfast(&b);
			G[a].pb({b,j});
			G[b].pb({a,j});
			deg[a]++;
			deg[b]++;
		}
		int st=0;
		if(Eulerian(n,st)){
			printf("TAK ");
			FindCircuit(n);
			printf("\n");
		}
		else{
			printf("NIE\n");
		}
		Clear(n,m);
	}

    return 0;
}
