#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=100000;
ll tree[4*MAXN+10],add[4*MAXN+10],mul[4*MAXN+10],a[MAXN+10],p;
void build(int k,int l,int r){
	add[k]=0;mul[k]=1;
	if(l==r){
		tree[k]=a[r];
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	tree[k]=(tree[k<<1]+tree[k<<1|1])%p;
}
void pushdown(int k,int l,int r){
	int mid=(l+r)>>1;
	tree[k<<1]=(tree[k<<1]*mul[k]+add[k]*(mid-l+1))%p;
	tree[k<<1|1]=(tree[k<<1|1]*mul[k]+add[k]*(r-mid))%p;
	mul[k<<1]=(mul[k]*mul[k<<1])%p;
	mul[k<<1|1]=(mul[k]*mul[k<<1|1])%p;
	add[k<<1]=(add[k<<1]*mul[k]+add[k])%p;
	add[k<<1|1]=(add[k<<1|1]*mul[k]+add[k])%p;
	mul[k]=1;
	add[k]=0;
}
void m_1(int k,int l,int r,int x,int y,ll v){
	if(y<l||x>r) return;
	if(x<=l&&y>=r){
		mul[k]=mul[k]*v%p;
		add[k]=add[k]*v%p;
		tree[k]=tree[k]*v%p;
		return;
	}
	pushdown(k,l,r);
	int mid=(l+r)>>1;
	m_1(k<<1,l,mid,x,y,v);
	m_1(k<<1|1,mid+1,r,x,y,v);
	tree[k]=(tree[k<<1]+tree[k<<1|1])%p;
}
void m_2(int k,int l,int r,int x,int y,ll v){
	if(y<l||x>r) return;
	if(x<=l&&y>=r){
		add[k]=(add[k]+v)%p;
		tree[k]=(tree[k]+v*(r-l+1)%p)%p;
		return;
	}
	pushdown(k,l,r);
	int mid=(l+r)>>1;
	m_2(k<<1,l,mid,x,y,v);
	m_2(k<<1|1,mid+1,r,x,y,v);
	tree[k]=(tree[k<<1]+tree[k<<1|1])%p;
}
ll query(int k,int l,int r,int x,int y){
	if(y<l||x>r) return 0;
	if(x<=l&&y>=r){
		return tree[k]%p;
	}
	pushdown(k,l,r);
	int mid=(l+r)>>1;
	return (query(k<<1,l,mid,x,y)+query(k<<1|1,mid+1,r,x,y))%p;
}
int main(){
	int n,m;
	cin>>n>>m>>p;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int op,x,y;
		ll z;
		cin>>op;
		if(op==1){
			cin>>x>>y>>z;
			m_1(1,1,n,x,y,z);
		}
		else if(op==2){
			cin>>x>>y>>z;
			m_2(1,1,n,x,y,z);
		}
		else{
			cin>>x>>y;
			cout<<query(1,1,n,x,y)<<endl;
		}
	}
	return 0;
}
