int rep[MAXN];
int ran[MAXN];
vector< pair<int, pii> > E;

void Prepare(int n){
	FOR(i,1,n+1){
		rep[i]=i;
	}
}

int Find(int x){
	if(rep[x]!=x) rep[x]=Find(rep[x]);
	return rep[x];
}

void Union(int a, int b){
	int x=Find(a), y=Find(b);
	if(ran[x]<ran[y]) rep[x]=y;
	else{
		rep[y]=x;
		if(ran[x]==ran[y]) ran[x]++;
	}
}

int MST_cost(){
	int res=0;
	sort(E.begin(), E.end());
	for(auto edge : E){
		if(Find(edge.nd.st)!=Find(edge.nd.nd)){
			Union(edge.nd.st, edge.nd.nd);
			res+=edge.st;
		}
	}
	return res;
}
