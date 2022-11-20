struct node{
	int x=0,prior=0,cnt=0,m=INF,min_pos=0;
	bool rev=false;
	node *l=0,*r=0;
};

typedef node* pnode;

pnode root;

inline int Cnt(pnode x){
	if(x) return x->cnt;
	return 0;
}

inline int Min(pnode x){
	if(x) return x->m;
	return INF;
}

inline int MinP(pnode x){
	if(x) return x->min_pos;
	return 0;
}

inline bool Rev(pnode& x){
	if(x) return x->rev;
	return false;
}

inline void Update(pnode& x){
	if(!x) return;
	x->cnt=Cnt(x->l)+Cnt(x->r)+1;
	if(x->x<Min(x->l) && x->x<Min(x->r)){
		x->m=x->x;
		x->min_pos=Cnt(x->l);
	}
	else{
		if(Min(x->l)<=Min(x->r)){
			x->m=Min(x->l);
			x->min_pos=MinP(x->l);
		}
		else{
			x->m=Min(x->r);
			x->min_pos=Cnt(x->l)+1+MinP(x->r);
		}
	}
	
}

inline void ChangeP(pnode x){
	x->min_pos=(x->cnt-x->min_pos-1);
}

inline void Push(pnode& x){
	if(Rev(x)){
		x->rev=false;
		swap(x->l,x->r);
		if(x->l){
			x->l->rev^=true;
			ChangeP(x->l);
		}
		if(x->r){
			x->r->rev^=true;
			ChangeP(x->r);
		}
	}
}

inline pair<pnode,pnode> Split(pnode t, int x, int add){
	if(!t) return {0,0};
	pair<pnode, pnode> res;
	Push(t);
	int curx=add+Cnt(t->l);
	
	if(curx<x){
		res.st=t;
		pair<pnode, pnode> tmp=Split(t->r,x,curx+1);
		t->r=tmp.st;
		res.nd=tmp.nd;
		Update(res.st);
	}
	else{
		res.nd=t;
		pair<pnode, pnode> tmp=Split(t->l,x,add);
		t->l=tmp.nd;
		res.st=tmp.st;
		Update(res.nd);
	}
	
	return res;
}

inline pnode Merge(pnode t1, pnode t2){
	if(!t1) return t2;
	if(!t2) return t1;
	
	pnode res;
	if(t1->prior>t2->prior){
		Push(t1);
		t1->r=Merge(t1->r,t2);
		res=t1;
	}
	else{
		Push(t2);
		t2->l=Merge(t1,t2->l);
		res=t2;
	}
	Update(res);
	return res;
}

inline void Insert(int x, int pos, int pr){
	if(!root){
		root=new node;
		root->x=x, root->prior=pr, root->m=x, root->min_pos=0;
		Update(root);
		return;
	}
	pair<pnode,pnode> tmp=Split(root,pos,0);
	pnode v=new node;
	v->x=x, v->prior=pr, v->m=x, v->min_pos=0;
	tmp.st=Merge(tmp.st,v);
	root=Merge(tmp.st,tmp.nd);
}

inline void Reverse(int a, int b){
	pair<pnode,pnode> p1=Split(root,a,0), p2=Split(p1.nd,b-a+1,0);
	if(p2.st){
		p2.st->rev^=true;
		ChangeP(p2.st);
	}
	root=Merge(p1.st,Merge(p2.st,p2.nd));
}

inline void Erase(int& pos){
	pair<pnode,pnode> tmp=Split(root,pos,0), tmp2=Split(tmp.nd,1,0);
	root=Merge(tmp.st,tmp2.nd);
}
