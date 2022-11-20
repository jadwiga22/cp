int C[MAXN][MAXN];
int dp[MAXK][MAXN];
     
inline void countDP(int a, int b, int& l, int& r, int& k){
	int mid=((a+b)>>1), opt=0;
	FOR(i,l,r+1){
		if(dp[k-1][i]+C[i+1][mid]<dp[k][mid]){
			dp[k][mid]=dp[k-1][i]+C[i+1][mid];
			opt=i;
		}
    }
	if(a<=mid-1) countDP(a,mid-1,l,opt,k);
    if(b>=mid+1) countDP(mid+1,b,opt,r,k);
}
     
inline void Solve(int& n, int& k){
	FOR(i,2,k+1){
		int a=1,b=n;
		countDP(a,b,a,b,i);
	}
	printf("%d", dp[k][n]);
}
