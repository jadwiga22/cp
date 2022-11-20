struct ev{
	int be,en,nr,box;
};

vii G[MAXN];
int num[MAXN];
int ST[MAXN];
int EN[MAXN];
int T[(MAXN<<1)];
int ans[MAXN];
int Pres[MAXN];
bool included[MAXN];
int ind=1, root;
vector<ev> E;
set<int> NPres;

inline void Read(int& n){
	FOR(i,1,n){
		int a,b,x;
		scanfast(&a);
		scanfast(&b);
		scanfast(&x);
		G[a].pb({b,x});
		G[b].pb({a,x});
	}
}

inline void DFS(int v){
	T[ind]=v;
	ST[v]=ind++;
	for(pii u : G[v]){
		if(!ST[u.st]){
			num[u.st]=u.nd;
			DFS(u.st);
		}
	}
	T[ind]=v;
	EN[v]=ind++;
}

inline int Sqrt(int x){
	ll d=1, g=x;
	while(d+1<g){
		ll s=((d+g)>>1);
		if(s*s>x) g=s;
		else d=s;
	}
	return d;
}

inline bool cmp(ev a, ev b){
	if(a.box!=b.box) return a.box<b.box;
	return a.en<b.en;
}

inline bool Ancestor(int& a, int& b){
	return (ST[a]<=ST[b] && EN[a]>=EN[b]);
}

inline void Preprocess(int n, int q){
	root=Sqrt((n<<1));
	FOR(i,0,q){
		int a,b;
		scanfast(&a);
		scanfast(&b);
		ev x;
		if(Ancestor(a,b)){
			x.be=ST[a]+1;
			x.en=ST[b];
		}
		else{
			if(Ancestor(b,a)){
				x.be=ST[b]+1;
				x.en=ST[a];
			}
			else{
				if(ST[a]<ST[b]){
					x.be=EN[a];
					x.en=ST[b];
				}
				else{
					x.be=EN[b];
					x.en=ST[a];
				}
			}
		}
		x.nr=i;
		x.box=(x.be/root);
		E.pb(x);
	}
	sort(E.begin(), E.end(), cmp);

	FOR(i,0,MAXN){
		NPres.insert(i);
	}
}

inline void Actualize(int& x){
	if(num[T[x]]>=MAXN || T[x]==1) return;
	if(included[T[x]]){
		included[T[x]]=false;
		Pres[num[T[x]]]--;
		if(!Pres[num[T[x]]]){
			NPres.insert(num[T[x]]);
		}
	}
	else{
		included[T[x]]=true;
		if(!Pres[num[T[x]]]){
			NPres.erase(num[T[x]]);
		}
		Pres[num[T[x]]]++;
	}
}

inline void Answer(int& q){
	int cur_be=1, cur_en=1;
	for(ev e : E){
		while(e.be<cur_be){
			cur_be--;
			Actualize(cur_be);
		}
		while(e.be>cur_be){
            Actualize(cur_be);
			cur_be++;
		}
		while(e.en<cur_en){
			Actualize(cur_en);
			cur_en--;
		}
		while(e.en>cur_en){
			cur_en++;
            Actualize(cur_en);
		}
		if(e.be<=e.en) ans[e.nr]=(*NPres.begin());
		else ans[e.nr]=0;
	}

	FOR(i,0,q){
	    cout<<ans[i]<<"\n";
    }
}

int main(){
	Read(n);
	DFS(1);
	Preprocess(n,q);
	Answer(q);

	return 0;
}
