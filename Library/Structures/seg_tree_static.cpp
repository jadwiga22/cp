struct node{
	int m=0;
	int lazy=0;
	node *left=0, *right=0;
};

node* root[MAXN];

node* Left(node* x){
	if(x==0) return 0;
	return x->left;
}

node* Right(node* x){
	if(x==0) return 0;
	return x->right;
}

int Mini(node* x){
	if(x==0) return 0;
	return x->m;
}

int Lazy(node* x){
	if(x==0) return 0;
	return x->lazy;
}

void Copy(node* oldx, node* newx){
	newx->left=Left(oldx);
	newx->right=Right(oldx);
	newx->m=Mini(oldx);
	newx->lazy=Lazy(oldx);
}

void Propagate(node* x, int s){
	if(s==1 || !Lazy(x)) return;

	node *l=new node;
	node *r=new node;

	Copy(Left(x),l);
	Copy(Right(x),r);

	l->lazy+=Lazy(x);
	r->lazy+=Lazy(x);

	l->m+=Lazy(x);
	r->m+=Lazy(x);

	x->left=l;
	x->right=r;
	x->m=min(Mini(Left(x)), Mini(Right(x)));
	x->lazy=0;

}

int Min(node* x, int be, int en, int a, int b){
	Propagate(x,en-be+1);
	if((be==a && en==b) || x==0) return Mini(x);
	int mid=((be+en)>>1), res=INF;
	if(a<=mid) res=min(res, Min(Left(x),be,mid,a,min(b,mid)));
	if(b>mid) res=min(res, Min(Right(x),mid+1,en,max(a,mid+1),b));
	return res;
}

void Add(node* newx, node* oldx, int be, int en, int a, int b, int val){
	Copy(oldx,newx);
	if(be==a && en==b){
		(newx->m)+=val;
		(newx->lazy)+=val;
		return;
	}
	int mid=((be+en)>>1);
	Propagate(newx,en-be+1);
	node *l=Left(oldx), *r=Right(oldx);
	if(a<=mid){
		l=new node;
		Add(l,Left(oldx),be,mid,a,min(b,mid),val);
	}
	if(b>mid){
		r=new node;
		Add(r,Right(oldx),mid+1,en,max(a,mid+1),b,val);
	}

	newx->left=l;
	newx->right=r;
	newx->m=min(Mini(Left(newx)), Mini(Right(newx)));
}
