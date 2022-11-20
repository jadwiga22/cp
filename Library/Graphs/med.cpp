#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+5, INF=2e9;

#define FOR(i,be,en) for(int i=be; i<en; i++)
#define vi vector<int>
#define pb push_back

int res=0;
int T[MAXN], C[MAXN];
int dp[2][2][MAXN];
bool onStack[MAXN];
bool vis[MAXN];
stack<int> S;
vi G[MAXN];

void Prepare(int n){
	FOR(i,1,n+1) cin>>C[i];
	
	FOR(i,1,n+1){
		cin>>T[i];
		if(T[i]) G[T[i]].pb(i);
	}
}

int Root(int v){
	S.push(v);
	onStack[v]=true;
	while(T[S.top()] && !onStack[T[S.top()]]){
		S.push(T[S.top()]);
		onStack[S.top()]=true;
	}
	return S.top();
}

void CalcDP(int v, int sp){
	vis[v]=true;
	bool sp_son=false;
	for(int u : G[v]){
		if(!vis[u]){
			if(u==sp) sp_son=true;
			CalcDP(u,sp);
			FOR(i,0,2){
				dp[i][0][v]+=max(dp[i][0][u], dp[i][1][u]);
				dp[i][1][v]+=dp[i][0][u];
			}
		}
	}
	FOR(i,0,2){
		dp[i][1][v]+=C[v];
	}
	if(T[v]==sp || sp_son) dp[1][1][v]=0;
	if(v==sp) dp[0][1][v]=dp[1][0][v]=0;
}

void Solve(int n){
	FOR(i,1,n+1){
		if(!vis[i]){
			int x=Root(i), tmp=0;
			CalcDP(x, T[x]);
			FOR(j,0,2){
				FOR(k,0,2){
					tmp=max(tmp,dp[j][k][x]);
				}
			}
			res+=tmp;
		}
	}
	cout<<res;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int n,m;
	cin>>n>>m;
	
	Prepare(n);
	Solve(n);
	
	return 0;
}
