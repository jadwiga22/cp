const int MAXN=19,MAXM=0,INF=0, MASK=(1<<MAXN);

int sat[MAXN];
int G[MAXN][MAXN];
ll dp[MASK][MAXN];
vi V;

inline bool cmp(int a, int b){
	return __builtin_popcount(a)<__builtin_popcount(b);
}

inline void CalcDP(int n){
	int M=(1<<n);
	FOR(i,0,M) V.pb(i);
	sort(V.begin(), V.end(),cmp);
	FOR(i,0,n){
		dp[(1<<i)][i]=sat[i];
	}
	FOR(m,1,M){
		int mask=V[m];
		FOR(last,0,n){
			if(!(mask&(1<<last))) continue;
			FOR(nxt,0,n){
				if(mask&(1<<nxt)) continue;
				//if there is no edge last-nxt then ...
				dp[mask|(1<<nxt)][nxt]=max(dp[mask|(1<<nxt)][nxt],dp[mask][last]+G[last][nxt]+sat[nxt]);
			}
		}
	}
}
