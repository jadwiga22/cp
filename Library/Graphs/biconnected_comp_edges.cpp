void Pop(pii e){
	vii E;
	pii rev={e.nd,e.st};
	while(!S.empty() && S.top()!=e && S.top()!=rev){
		E.pb(S.top());
		Num.pop();
		S.pop();
	}
	if(!S.empty()){
		E.pb(S.top());
		Num.pop();
		S.pop();
	}
}

int DFS(int v, int f, int& t){
	low[v]=pre[v]=t++;
	vis[v]=true;
	int res=low[v];
	for(pii x : G[v]){
		int u=x.st;
		if(onS[x.nd]) continue;
		if(u==f) continue;
		if(!onS[x.nd]){
			S.push({v,u});
			Num.push(x.nd);
			onS[x.nd]=true;
		}
		
		if(!vis[u]){
			int cur=DFS(u,v,t);
			low[v]=min(low[u],low[v]);
			if(cur>=pre[v]){
				Pop({v,u});
			}
			res=min(res,cur);
		}
		else{
			low[v]=min(low[v],pre[u]);
		}
	}
	res=min(res,low[v]);
	return res;
}
