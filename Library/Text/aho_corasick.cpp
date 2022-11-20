int T[27][MAXN*MAXN];
int S[MAXN];
int ind=1;
int fail[MAXN*MAXN];
int Nr[MAXN*MAXN];
char Dir[MAXN];
char Te[MAXN*MAXN];
int Vert[MAXN];
int Pos[MAXN*MAXN];
int PosS[MAXN];
bool found[MAXN*MAXN];
int en=0;

void AddTrie(string& s, int& nr){
	int i=0,j=0;
	while(j<(int)s.size() && T[s[j]-'a'][i]){
		i=T[s[j]-'a'][i];
		j++;
	}
	while(j<(int)s.size()){
		T[s[j]-'a'][i]=ind;
		i=ind++;
		j++;
	}	
	Vert[nr]=i;
}

void BFSFail(int w){
	queue<int> Q;
	Q.push(w);
	while(!Q.empty()){
		int v=Q.front();
		Q.pop();
		FOR(i,0,26){
			if(T[i][v]){
				int u=fail[v];
				while(!T[i][u] && u){
					u=fail[u];
				}
				if(u==v) fail[T[i][v]]=u;
				else fail[T[i][v]]=T[i][u];
				Q.push(T[i][v]);
			}
		}
	}
}

void AhoCorasick(char dir, int w){
	FOR(i,0,ind) found[i]=false;
	int v=0;
	 FOR(pos,0,en){
	 	while(v && !T[Te[pos]-'a'][v]){
			v=fail[v];
		}
		if(T[Te[pos]-'a'][v]) v=T[Te[pos]-'a'][v];
		
		Pos[v]=pos;
		found[v]=true;
	}
	FOR(i,0,ind){
		if(!found[i]) continue;
		int u=fail[i];
		while(u && !found[u]){
			Pos[u]=Pos[i];
			found[u]=true;
			u=fail[u];
		}
	}
//	FOR(i,0,w){
//		if(!found[Vert[i]]) continue;
//		PosS[i]=Nr[Pos[Vert[i]]-S[i]+1];
//		Dir[i]=dir;
//	}
}
