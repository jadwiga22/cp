ll dist[MAXN][MAXN];
ll res=INF;

void FloWar(int n, int m){
	FOR(i,1,n+1){
		FOR(j,1,n+1) dist[i][j]=INF;
		dist[i][i]=0;
	}
	
	FOR(i,0,m){
		int a,b,c;
		scanfast(&a);
		scanfast(&b);
		scanfast(&c);
		dist[a][b]=min(dist[a][b],(ll) c);
		if(a==b) res=min(res,(ll) c);
	}
		
	FOR(k,1,n+1){
		FOR(i,1,n+1){
			FOR(j,1,n+1)
				dist[i][j]=min(dist[i][j], dist[i][k]+dist[k][j]);
		}
	}
}

void MinCycl(int n){
	FOR(i,1,n+1){
		FOR(j,1,n+1){
			if(j==i) continue;
			res=min(dist[i][j]+dist[j][i],res);
		}
	}
}
