vi G[(MAXN<<1)]; // v <= MAXN, not v == v + MAXN
vi revG[(MAXN<<1)];
bool onStack[(MAXN<<1)];
bool vis[(MAXN<<1)];
int SCCnum[(MAXN<<1)];
vi CurSCC;
stack<int> S;
int val[(MAXN<<1)];

void Reverse(int n){
	FOR(i,1,n+1){
		for(int x : G[i]){
			revG[x].pb(i);
		}
		for(int x : G[MAXN+i]){
			revG[x].pb(MAXN+i);
		}
	}
}

void DFS(int v){
	onStack[v]=true;
	for(int u : revG[v]){
		if(!onStack[u]){
			DFS(u);
		}
	}
	S.push(v);
}

void FindSCC(int v){
	vis[v]=true;
	CurSCC.pb(v);
	for(int u : G[v]){
		if(!vis[u]){
			SCCnum[u]=SCCnum[v];
			FindSCC(u);
		}
	}
}

bool GiveVal(){
	int predest=-1;
	for(int x : CurSCC){
		if(x>=MAXN && val[x-MAXN]!=-1){
			predest=!val[x-MAXN];
		}
		if(x<=MAXN && val[x+MAXN]){
			predest=!val[x+MAXN];
		}
	}
	if(predest==-1) predest=1;
	
	for(int x : CurSCC){
		val[x]=predest;
		if(x>=MAXN && val[x]==val[x-MAXN]) return false;
		if(x<MAXN && val[x]==val[x+MAXN]) return false;
	} 
	CurSCC.resize(0);
	return true;
}

bool TwoSat(int n){
	FOR(i,1,n+1){
		if(!onStack[i]) DFS(i);
	}
	int num=1;
	while(!S.empty()){
		int v=S.top();
		S.pop();
		if(SCCnum[v]) continue;
		SCCnum[v]=num++;
		FindSCC(v);
		if(!GiveVal()) return false;
	}
	return true;
}


int main(){
	int n,m;
	scanfast(&n);
	scanfast(&m);
	FOR(i,0,m){
		int a,b,c;
		scanfast(&a);
		scanfast(&b);
		scanfast(&c);
		if(c){
			G[a].pb(b);
			G[b].pb(a);
			G[MAXN+a].pb(MAXN+b);
			G[MAXN+b].pb(MAXN+a);
		}
		else{
			G[a].pb(MAXN+b);
			G[MAXN+b].pb(a);
			G[MAXN+a].pb(b);
			G[b].pb(MAXN+a);
		}
	}
	
	Reverse(n);
	if(!TwoSat(n)){
		printf("Impossible");
	}
	else{
		int res=0;
		FOR(i,1,n+1){
			if(val[i]) res++;
		}
		printf("%d\n",res);
		FOR(i,1,n+1){
			if(val[i]){
				printf("%d ",i);
			}
		}
	}
	
	
	
	return 0;
}
