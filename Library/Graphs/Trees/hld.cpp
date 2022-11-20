//Jadwiga Swierczynska

#include<bits/stdc++.h>
using namespace std;

int ind=1;
int dict[MAXN];
int rev[MAXN];
int T[(B<<1)];
int pre[MAXN];
int post[MAXN];
int pathfath[MAXN];
bool vis[MAXN];
int subt[MAXN];
int father[MAXN];
vi G[MAXN];

void DFS(int v, int& pre_time, int& post_time){
	vis[v]=true;
	pre[v]=pre_time++;
	for(int u : G[v]){
		if(!vis[u]){
			father[u]=v;
			DFS(u,pre_time,post_time);
			subt[v]+=subt[u];
		}
	}
	subt[v]++;
	post[v]=post_time++;
}

void Decomp(int v){ // uzywa tej samej tablicy vis
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

inline bool Ancestor(int v ,int u){
	return pre[v]<=pre[u] && post[v]>=post[u];
}

inline void Add(int a, int b, int val){
	a+=B, b+=B;
	while(a<b){
		if(a&1){
			T[a]+=val;
			a++;
		}
		if(!(b&1)){
			T[b]+=val;
			b--;
		}
		a>>=1;
		b>>=1;
	}
	if(a==b) T[a]+=val;
}

inline int Val(int pos){
	int res=0;
	pos+=B;
	while(pos){
		res+=T[pos];
		pos>>=1;
	}
	return res;
}

inline void AddPath(int a, int b){
	while(!Ancestor(rev[pathfath[a]],b) && !Ancestor(rev[pathfath[b]],a)){
		Add(pathfath[a],dict[a],1);
		Add(pathfath[b],dict[b],1);
		a=father[rev[pathfath[a]]];
		b=father[rev[pathfath[b]]];
	}
	if(Ancestor(rev[pathfath[a]],b)){
		while(pathfath[a]!=pathfath[b]){
			Add(pathfath[b],dict[b],1);
			b=father[rev[pathfath[b]]];
		}
	}
	if(Ancestor(rev[pathfath[b]],a)){
		while(pathfath[a]!=pathfath[b]){
			Add(pathfath[a],dict[a],1);
			a=father[rev[pathfath[a]]];
		}
	}
	if(Ancestor(a,b)){
		Add(dict[a]+1,dict[b],1);
	}
	else{
		Add(dict[b]+1,dict[a],1);
	}
}

inline int Weight(int a, int b){
	if(Ancestor(a,b)) return Val(dict[b]);
	return Val(dict[a]);
}


int main(){
	int pr=1,po=1;
	DFS(1,pr,po);
	FOR(i,1,n+1) vis[i]=false;
	Decomp(1);
	
	return 0;
}
