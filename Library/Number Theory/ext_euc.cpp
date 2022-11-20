#pragma GCC optimize("Ofast","unroll-loops","no-stack-protector")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int MAXN=0,MAXM=0,INF=0;

#define FOR(i,be,en) for(int i=be; i<en; i++)
#define FORD(i,be,en) for(int i=be; i>en; i--)
#define pb push_back
#define vi vector<int>
#define pii pair<int,int>
#define st first
#define nd second
#define vii vector<pii>

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

pii ExtEuc(int a, int b){ //a*res.st+b*res.nd==gcd(a,b)
	if(!b) return {1,0};
	pii res=ExtEuc(b,a%b);
	int buff=res.st-res.nd*(a/b);
	return {res.nd,buff};
}

int RevMod(int a, int b){ // (a*res)%b=1
	if(__gcd(a,b)!=1) return -1;
	if(a>b) a%=b;
	pii tmp=ExtEuc(b,a);
	if(tmp.nd<0) tmp.nd+=b;
	return tmp.nd;
}

int main(){

	int t;
	scanfast(&t);
	
	FOR(i,0,t){
		int n,p;
		scanfast(&n);
		scanfast(&p);
		printf("%d\n", RevMod(n,p));
	}
	
	return 0;
}
