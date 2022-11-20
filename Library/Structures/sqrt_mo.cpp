struct query{
	int a,b,box,nr;
};

set<pii> S;
int T[MAXN];
int Ans[MAXN];
unordered_map<int,int> Occ;
query Q[MAXN];
int root;

int Sqrt(int n){
	int d=1,g=n;
	while(d+1<g){
		int s=((d+g)>>1);
		if(1LL*s*s<=n) d=s;
		else g=s;
	}
	return d;
}

bool cmp(query a, query b){
	if(a.box!=b.box) return a.box<b.box;
	return a.b<b.b;
}

void Insert(int i){
	int o=Occ[i]++;
	S.erase({-o,i});
	S.insert({-o-1,i});
}

void Delete(int i){
	int o=--Occ[i];
	S.erase({-o-1,i});
	S.insert({-o,i});
}

void Process(int n, int q){
	int be=1,en=0;
	FOR(i,1,n+1){
		if(!Occ.count(T[i])){
			Occ.insert({T[i],0});
			S.insert({0,T[i]});
		} 
	}
	FOR(i,1,q+1){
		while(Q[i].a<be){
			be--;
			Insert(T[be]);
		}
		while(Q[i].a>be){
			Delete(T[be]);
			be++;
		}
		while(Q[i].b<en){
			Delete(T[en]);
			en--;
		}
		while(Q[i].b>en){
			en++;
			Insert(T[en]);
		}
		Ans[Q[i].nr]=(S.begin()->nd);
	}
}
