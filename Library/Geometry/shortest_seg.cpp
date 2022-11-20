struct point{
	int x,y;
};

point T[MAXN];
point Strip[MAXN];

inline bool cmp(point a, point b){
	if(a.x!=b.x) return a.x<b.x;
	return a.y>b.y;
}

inline bool cmpY(point a, point b){
	return a.y>b.y;
}

inline ld dist(point a, point b){
	return (ld)(a.x-b.x)*(ld)(a.x-b.x)+(ld)(a.y-b.y)*(ld)(a.y-b.y);
}

inline ld Brut(int a, int b){
	ld res=INF;
	FOR(i,a,b){
		FOR(j,i+1,b+1){
			res=min(res,dist(T[i],T[j]));
		}
	}
	return res;
}

inline ld Shortest(int be, int en){
	if(en-be<=2){
		return Brut(be,en);
	}
	int mid=((be+en)>>1);
	ld res=INF;
	res=min(res,Shortest(be,mid));
	res=min(res,Shortest(mid+1,en));
	int x=T[mid].x, ind=mid, ind_s=0;
	while(ind>=be && T[ind].x+res>=x){
		Strip[ind_s]=T[ind];
		ind_s++;
		ind--;
	} 
	ind=mid+1;
	while(ind<=en && T[ind].x-res<=x){
		Strip[ind_s]=T[ind];
		ind_s++;
		ind++;
	}
	sort(Strip,Strip+ind_s,cmpY);
	FOR(i,0,ind_s){
		FOR(j,i+1,min(ind_s,i+6)){
			res=min(res,dist(Strip[i], Strip[j]));
		}
	}
	return res;
}

