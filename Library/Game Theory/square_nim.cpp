int Nim[MAXA];
bool taken[MAXA];

void Prepare(){
	FOR(i,1,MAXA){
		int j=1,lim=0;
		while(i>=j*j){
			taken[Nim[i-j*j]]=true;
			lim=max(lim,Nim[i-j*j]);
			j++;
		}
		j=0;
		while(taken[j]){
			j++;
		}
		Nim[i]=j;
		FOR(k,0,lim+1) taken[k]=false;
	}
}

int main(){
	Prepare();

	int q;
	scanfast(&q);
	
	FOR(i,0,q){
		int n;
		scanfast(&n);
		int res=0;
		FOR(j,0,n){
			int a;
			scanfast(&a);
			res^=Nim[a];
		}
		if(res) printf("TAK\n");
		else printf("NIE\n");
	}
	
	return 0;
}
