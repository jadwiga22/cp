struct node{
	node *l=0,*r=0;
	int s=0;
};

node* Left(node* x){
	if(x) return x->l;
	return 0;
}

node* Right(node* x){
	if(x) return x->r;
	return 0;
}

int Sum(node* x){
	if(x) return x->s;
	return 0;
}

void Add(node* x, int be, int en, int a, int b, int val){
	if(be==a && en==b){
		(x->s)+=val;
		return;
	}
	int mid=((be+en)>>1);
	if(a<=mid){
		if(!Left(x)) (x->l)=new node;
		Add(Left(x),be,mid,a,min(b,mid),val);
	}
	if(b>mid){
		if(!Right(x)) (x->r)=new node;
		Add(Right(x),mid+1,en,max(a,mid+1),b,val);
	}
}

int Val(node* x, int be, int en, int pos){
	int res=Sum(x), mid=((be+en)>>1);
	if(be==en) return res;
	if(pos<=mid) res+=Val(Left(x),be,mid,pos);
	else res+=Val(Right(x),mid+1,en,pos);
	return res;
}
