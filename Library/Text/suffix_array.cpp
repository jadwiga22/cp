int KMR_T[LOG][MAXN];
pair<pii,int> Num[MAXN];
int SA[MAXN];

string s;
int n;

inline void KMR(){	
	FOR(i,0,n){
		KMR_T[0][i]=s[i]-'a'+1;
	}
	
	int jump=1;
	

	FOR(i,1,LOG){
		FOR(j,0,n){
			if(j+jump>=(int)s.size()){
				Num[j]={{KMR_T[i-1][j],-1},-j};
			}
			else{
				Num[j]={{KMR_T[i-1][j],KMR_T[i-1][j+jump]},-j};
			}
		}
		sort(Num,Num+n);
		int new_num=0;
		pii pre={-1,-1};
		FOR(j,0,n){
			if((pre!=Num[j].st) || (pre.nd==-1)){
				pre=Num[j].st;
				new_num++;
			} 
			KMR_T[i][-Num[j].nd]=new_num;
		}
		jump<<=1;
	}
}

inline bool cmp(int a, int b){	
	return KMR_T[LOG-1][a]<KMR_T[LOG-1][b];
}

void MakeSA(){
	KMR();
	
	FOR(i,0,n) SA[i]=i;
	
	sort(SA, SA+n, cmp);
}
