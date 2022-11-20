inline bool Equal(point& a, point& b){
	return a.x==b.x && a.y==b.y;
}

inline ll Vector(point& a, point& b, point& c){ // <0 if b is on the right side of a
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
