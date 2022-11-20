struct point{
	int x,y;
};

point T[MAXN];
point zero;

inline int Vector(point& a, point& b){
	return ((int)a.x*b.y-(int)a.y*b.x);
}

inline int dist(point& a){
	return (int)a.x*a.x+(int)a.y*a.y;
}

inline bool Equal(point& a, point& b){
	return a.x==b.x && a.y==b.y;
}

inline bool cmp(point a, point b){ //anti-clockwise, closer to {0,0}
	if(Equal(a,zero) || Equal(b,zero)) return Equal(a,zero);
	int tmp=Vector(a,b);
	if(tmp) return tmp>0;
	return dist(a)<dist(b);
}

inline void Normalize(point& a, point& b){
	a.x-=b.x;
	a.y-=b.y;
}



int Position(point x, int n){ //-1 in, 0 on the side, 1 out
	int pos1=Vector(T[1],x), pos2=Vector(T[n-1],x);
	if(pos1<0 || pos2>0) return -1;
	if((!pos1 && dist(x)<=dist(T[1])) || (!pos2 && dist(x)<=dist(T[n-1]))) return 0;
	int d=1,g=n-1;
	while(d+1<g){
		int s=((d+g)>>1);
		if(Vector(T[s],x)>=0) d=s;
		else g=s;
	}
	point en=T[g];
	Normalize(en,T[d]);
	Normalize(x,T[d]);
	int pos=Vector(en,x);
	if(pos>0) return 1;
	if(!pos) return 0;
	return -1;
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
	
	sort(T,T+n,cmp);
	
	int m;
	scanfast(&m);
	
	FOR(i,0,m){
		point x;
		scanfast(&x.x);
		scanfast(&x.y);
		Normalize(x,zero);
		int pos=Position(x,n);
		if(pos==-1) printf("na zewnatrz\n");
		if(pos==1) printf("wewnatrz\n");
		if(!pos) printf("na brzegu\n");
	}
	
	return 0;
}
