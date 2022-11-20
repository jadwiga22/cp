int pre[MAXN];
pii interval[MAXN];
vi G[MAXN]; 

void DFS(int v, int& pre_time){
    pre[v]=pre_time++;
    int be=pre[v], en=pre[v];
    for(int u : G[v]){
        if(!pre[u]){
            height[u]=height[v]+1;
            DFS(u, pre_time);
            en=max(en, interval[u].nd);
        }
    }
    interval[v]={be,en};
}
