void MatrixMult(int a[MAXN][MAXN], int b[MAXN][MAXN]){
    FOR(i,0,MAXN){
        FOR(j,0,MAXN){
            t1[i][j]=a[i][j];
            t2[i][j]=b[i][j];
            t3[i][j]=0;
        }
    }
    FOR(i,0,MAXN){
        FOR(j,0,MAXN){
            FOR(k,0,MAXN){
                t3[i][j]=1LL*(t3[i][j]+(1LL*t1[i][k]*t2[k][j]))%MOD;
            }
        }
    }
}

void MatrixPower(int n){
    if(n==1) return;
    MatrixPower((n>>1));

    MatrixMult(t3,t3);
    if((n&1)){
        MatrixMult(t3,M);
    }
}
