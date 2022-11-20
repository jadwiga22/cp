struct rect{
	ll x,y,a;
};

pll Fun[MAXN];
ll dp[MAXN];
rect T[MAXN];

bool Cmp(rect a, rect b){
	return a.x<b.x;
}

bool Delete(int& ind, pll last){
	ld tmp=((ld) (Fun[ind-1].nd-last.nd))/((ld) (last.st-Fun[ind-1].st));
	tmp*=((ld) (Fun[ind-2].st-last.st));
	return tmp>=last.nd-Fun[ind-2].nd;
}

void Actualize(int& ind, pll last){
	while(ind>1 && Delete(ind, last))	ind--;
	Fun[ind++]=last;
}

ll F(int i, ll x){
	return Fun[i].st*x+Fun[i].nd;
}

void ActualizePos(int& pos, int& ind, ll x){
	if(ind-1<pos) pos=ind-1;
	while(pos<ind-1 && F(pos,x)<F(pos+1,x)) pos++;
}

void Prepare(int n){
	FOR(i,0,n){
		cin>>T[i].x>>T[i].y>>T[i].a;
	}
	sort(T, T+n, Cmp);
}

ll MaxVal(int n){
	dp[0]=T[0].x*T[0].y-T[0].a;
	int ind=0, pos=0;
	Actualize(ind, {T[0].x, dp[0]});
	FOR(i,1,n){
		ActualizePos(pos,ind,-T[i].y);
		dp[i]=T[i].x*T[i].y-T[i].a+F(pos,-T[i].y);
		dp[i]=max(dp[i], T[i].x*T[i].y-T[i].a);
		Actualize(ind,{T[i].x, dp[i]});
	}
	ll res=dp[0];
	FOR(i,1,n) res=max(res,dp[i]);
	return res;
}
