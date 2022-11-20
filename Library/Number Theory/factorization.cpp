vl Div;
ll C=0;

inline ll Mult(ll a, ll b, ll m){
    ll res=0;
    while(b>0){
        if(b&1) res=(res+a)%m;
        b>>=1;
        a=(a<<1)%m;
    }
    return res;
}

inline ll Pow(ll x, ll a, ll m){
    if(!a) return 1%m;
    ll res=Pow(x,(a>>1),m);
    res=Mult(res,res,m);
    if(a&1) res=Mult(res,x,m);
    return res;
}

inline bool isPrime(ll n){
    if(n==2) return true;
    if(n<2 || !(n&1)) return false;
    FOR(i,0,5){
        ll cur=rand()%(n-2)+2, d=n-1,r=0;
        while(!(d&1)){
            r++;
            d>>=1;
        }
        cur=Pow(cur,d,n);
        if(cur==1 || (cur==n-1)) continue;
        while(r && cur!=n-1){
            r--;
            cur=Mult(cur,cur,n);
            if(cur==1) return false;
        }
        if(cur!=(n-1)) return false;
    }
    return true;
}

inline ll F(ll x, ll n){
    return (Mult(x,x,n)+C)%n;
}

inline ll FindDiv(ll n){
    C=rand()%10;
    ll x=rand()%(n-1)+1, y=F(x,n);
    while(x==y){
        x=rand()%(n-1)+1, y=F(x,n);
    }
    while(__gcd(abs(x-y),n)==1){
        x=F(x,n);
        y=F(F(y,n),n);
        if(x==y) break;
    }
    if(x==y) return FindDiv(n);
    return __gcd(abs(x-y),n);
}

inline void Factorize(ll n){
    while(n>1 && !isPrime(n)){
        ll x=FindDiv(n);
        Factorize(x);
        n/=x;
    }
    if(n>1) Div.pb(n);
}
