int KMR_T[LOG][MAXN];
pair<pii,int> Num[MAXN];

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

inline int CommonPart(int a, int b){
	int res=0;
	
	FORD(i,LOG-1,-1){
		if((KMR_T[i][a]==KMR_T[i][b] && KMR_T[i][a] && KMR_T[i][b])){
			int add=(1<<i);
			res+=add;
			a+=add;
			b+=add;
		}
	}
	
	return res;
}

