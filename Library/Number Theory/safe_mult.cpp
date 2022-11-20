inline ll Mult(ll a, ll b, ll m){
    ll res=0;
    while(b>0){
        if(b&1) res=(res+a)%m;
        b>>=1;
        a=(a<<1)%m;
    }
    return res;
}
