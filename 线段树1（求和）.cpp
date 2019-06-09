#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=100000;
ll tree[4*MAXN+10],v[MAXN],add[MAXN*4+10];
int n,m;
void build(int k,int l,int r){
	if(l==r){
		tree[k]=v[l];
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	tree[k]=tree[k<<1]+tree[k<<1|1];
}
void Add(int k,int l,int r,int v){
	add[k]+=v;
	tree[k]+=(r-l+1)*v;
}
void pushdown(int k,int l,int r){
	int mid=(l+r)>>1;
	if(add[k]==0) return;
	Add(k<<1,l,mid,add[k]);
	Add(k<<1|1,mid+1,r,add[k]);
	add[k]=0;
}
void modify(int k,int l,int r,int x,int y,int v){
	if(x<=l&&y>=r) return Add(k,l,r,v);
	int mid=(l+r)>>1;
	pushdown(k,l,r);
	if(x<=mid) modify(k<<1,l,mid,x,y,v);
	if(y>mid) modify(k<<1|1,mid+1,r,x,y,v);
	tree[k]=tree[k<<1]+tree[k<<1|1];
}
ll query(int k,int l,int r,int x,int y){
	if(x<=l&&y>=r) return tree[k];
	int mid=(l+r)>>1;
	pushdown(k,l,r);
	ll res=0;
	if(x<=mid) res+=query(k<<1,l,mid,x,y);
	if(y>mid) res+=query(k<<1|1,mid+1,r,x,y);
	return res;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>v[i];
	}
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int op,x,y,z;
		cin>>op;
		if(op==1){
			cin>>x>>y>>z;
			modify(1,1,n,x,y,z);
		}
		else{
			cin>>x>>y;
			cout<<query(1,1,n,x,y)<<endl;
		}
	}
	return 0;
}
