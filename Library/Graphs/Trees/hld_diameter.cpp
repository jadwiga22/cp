int ind=1,ans=0;
int seq[MAXN];
int C[(B<<1)];
int M[(B<<1)];
int l[2][MAXN];
int son[2][MAXN];
int depth[MAXN];
int subt[MAXN];
bool vis[MAXN];
int dict[MAXN];
int rev[MAXN];
int pathfath[MAXN];
int father[MAXN];

vi G[MAXN];

inline void Change(int pos, int val){
	pos+=B;
	M[pos]=val;
	while(pos>1){
		pos>>=1;
		M[pos]=max(M[(pos<<1)], M[(pos<<1)+1]);
	}
}

inline int MaxM(int a, int b){
	a+=B, b+=B;
	int res=0;
	while(a<b){
		if(a&1){
			res=max(res,M[a]);
			a++;
		}
		if(!(b&1)){
			res=max(res,M[b]);
			b--;
		}
		a>>=1;
		b>>=1;
	}
	if(a==b) res=max(res,M[a]);
	return res;
}

inline void ChangeC(int x, int be, int en, int a, int b, int val){
	if(be==a && en==b){
		C[x]=val;
		ans=max(ans,val+MaxM(a,b));
		return;
	}
	int mid=((be+en)>>1), L=(x<<1), R=L+1;
	if(a<=mid) ChangeC(L,be,mid,a,min(b,mid),val);
	if(b>mid) ChangeC(R,mid+1,en,max(a,mid+1),b,val);
}

inline int Val(int pos){
	pos+=B;
	int res=C[pos];
	while(pos>1){
		pos>>=1;
		res=max(res,C[pos]);
	}
	return res;
}

inline void DFS(int v){
	vis[v]=true;
	for(int u : G[v]){
		if(!vis[u]){
			depth[u]=depth[v]+1;
			DFS(u);
			subt[v]+=subt[u];
			father[u]=v;
		}
	}
	subt[v]++;
}

inline void Decomp(int v){
	vis[v]=true;
	dict[v]=ind++;
	rev[dict[v]]=v;
	if(!pathfath[v]) pathfath[v]=dict[v];
	for(int u : G[v]){
		if(!vis[u] && subt[u]>=(subt[v]>>1)){
			pathfath[u]=pathfath[v];
			Decomp(u);
			break;
		}
	}
	for(int u : G[v]){
		if(!vis[u]){
			Decomp(u);
		}
	}
}

inline void ActualizeLight(int v, int val ,int s){
	if(!v) return;
	if(l[0][v]<=val){
		swap(l[0][v],val);
		swap(son[0][v],s);
	} 
	if(l[1][v]<=val && s!=son[0][v]){
		swap(l[1][v],val);
		swap(son[1][v],s);
	}
	
	Change(v,l[0][v]-2*depth[rev[v]]);
	ans=max(ans,l[0][v]+l[1][v]-(depth[rev[v]]<<1));
	ans=max(ans,Val(v)+l[0][v]-(depth[rev[v]]<<1));
}

inline void Actualize(int v, int cur_depth){
	bool first=true;
	while(v){
		int d=pathfath[rev[v]],g=v;
		if(!first){
			g--;
		}
		else first=false;
		if(d<=g && Val(d)<cur_depth){
			ChangeC(1,0,B-1,d,g,cur_depth);
		} 
		else if(d<=g && Val(g)<cur_depth){
			while(d+1<g){
				int s=((d+g)>>1);
				if(Val(s)>cur_depth) d=s;
				else g=s;
			}
			ChangeC(1,0,B-1,g,v-1,cur_depth);
		}
		int pre=pathfath[rev[v]];
		v=dict[father[rev[pathfath[rev[v]]]]];
		ActualizeLight(v,cur_depth,pre);
	}
}



int main(){
	int n;
	scanfast(&n);
	
	FOR(i,2,n+1){
		scanfast(&seq[i]);
		G[seq[i]].pb(i);
		G[i].pb(seq[i]);
	}
	
	DFS(1);
	FOR(i,1,n+1) vis[i]=false;
	Decomp(1);

	
	FOR(i,1,n+1){
		Change(dict[i],-(depth[i]<<1));
	}
	
	FOR(i,2,n+1){
		Actualize(dict[i],depth[i]);
		printf("%d\n",ans);
	}
	
	return 0;
}
