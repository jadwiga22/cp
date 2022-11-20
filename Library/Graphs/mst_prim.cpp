int G[MAXN][MAXN];
bool inMST[MAXN];
int dist[MAXN];
priority_queue< pii > PQ;

inline ll MST(int& n){
	ll res=0;
	FOR(i,0,n+2) dist[i]=INF;
	dist[n]=0;
	
	PQ.push({0,n});
	while(!PQ.empty()){
		auto v=PQ.top();
		PQ.pop();
		if(inMST[v.nd]) continue;
		inMST[v.nd]=true;
		res+=(-v.st);
		FOR(i,0,n+2){
			if(!inMST[i] && dist[i]>G[v.nd][i]){
				dist[i]=G[v.nd][i];
				PQ.push({-G[v.nd][i],i});
			}
		}
	}
	return res;
}
