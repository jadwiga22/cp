int PrefSuf(string s){
    KMP[0]=-1;
    FOR(i,0,s.size()){
        int t=KMP[i];
        while(t>-1 && s[t]!=s[i]){
            t=KMP[t];
        }
        KMP[i+1]=++t;
    }
    return KMP[s.size()];
}

