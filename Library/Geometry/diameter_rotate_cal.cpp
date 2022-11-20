#pragma GCC optimize("Ofast","unroll-loops","no-stack-protector")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int MAXN=5e5+5,MAXM=0,INF=2e9;

#define FOR(i,be,en) for(int i=be; i<en; i++)
#define FORD(i,be,en) for(int i=be; i>en; i--)
#define pb push_back
#define vi vector<int>
#define pii pair<int,int>
#define st first
#define nd second
#define vii vector<pii>

struct point{
	int x,y;
};

point T[MAXN];
int nxt[MAXN];
vector<point> Conv;
point zero;

void scanfast(int* a){
	register char c=0;
	while(c<33) c=getc_unlocked(stdin);
	int sign=1;
	if(c=='-'){
		sign=-1;
		c=getc_unlocked(stdin);
	}
	(*a)=0;
	while(c>32){
		(*a)=10*(*a)+c-'0';
		c=getc_unlocked(stdin);
	}
	(*a)*=sign;
}

void scanfastC(char* a){
	register char c=0;
	while(c<33) c=getc_unlocked(stdin);
	(*a)=c;
}

void scanfastLL(ll* a){
	register char c=0;
	while(c<33) c=getc_unlocked(stdin);
	(*a)=0;
	ll sign=1;
	if(c=='-'){
		sign=-1;
		c=getc_unlocked(stdin);
	}
	while(c>32){
		(*a)=10LL*(*a)+c-'0';
		c=getc_unlocked(stdin);
	}
	(*a)*=sign;
}

inline bool Equal(point& a, point& b){
	return a.x==b.x && a.y==b.y;
}

inline ll Vector(point a, point b, point c){
	a.x-=c.x, b.x-=c.x;
	a.y-=c.y, b.y-=c.y;
	return 1LL*a.x*b.y-1LL*a.y*b.x;
}

inline ll dist(point& a, point& b){
	return 1LL*(a.x-b.x)*(a.x-b.x)+1LL*(a.y-b.y)*(a.y-b.y);
}

inline ll Area(point& a, point& b, point& c){
	return abs(1LL*(b.x-a.x)*(c.y-a.y)-1LL*(b.y-a.y)*(c.x-a.x));
}

inline void Normalize(point& a, point& b){
	a.x-=b.x, a.y-=b.y;
}

bool cmp(point a, point b){ //anti-clockwise, further from zero
	if(Equal(a,zero) || Equal(b,zero)) return Equal(a,zero);
	ll tmp=Vector(b,a,zero);
	if(tmp) return tmp<0;
	return dist(a,zero)>dist(b,zero);
}

void ConvexHull(int n){
	Conv.pb(T[0]);
	int ind=1;
	while(ind<n && Equal(zero,T[ind])) ind++;
	FOR(i,ind,n){
		while(Conv.size()>2 && Vector(Conv[Conv.size()-1],T[i],Conv[Conv.size()-2])<=0)
			Conv.pop_back();
		Conv.pb(T[i]);
		while(i<n-1 && !Vector(T[i],T[i+1],zero)) i++;
	}
}

ll Diameter(){
	FOR(i,0,(int)Conv.size()-1)
		nxt[i]=i+1;
	nxt[Conv.size()-1]=0;
	int en=1;
	ll res=0;
	FOR(be,0,(int)Conv.size()){
		res=max(res,dist(Conv[be],Conv[en]));
		while(Area(Conv[be],Conv[nxt[be]],Conv[en])<Area(Conv[be],Conv[nxt[be]],Conv[nxt[en]])){
			en=nxt[en];
			res=max(res,dist(Conv[be],Conv[en]));
		}
		res=max(res,dist(Conv[be],Conv[en]));
	}
	return res;
}


int main(){
	int n;
	scanfast(&n);
	
	zero.x=zero.y=INF;
	FOR(i,0,n){
		scanfast(&T[i].x);
		scanfast(&T[i].y);
		if(T[i].x<zero.x || (T[i].x==zero.x && T[i].y<zero.y)) zero=T[i];
	}
	
	FOR(i,0,n) Normalize(T[i],zero);
	Normalize(zero,zero);
	sort(T,T+n,cmp);
	
	ConvexHull(n);
	
	printf("%Lf", sqrt((ld)Diameter()));

	
	return 0;
}
