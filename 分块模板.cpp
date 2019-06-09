#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[100010],sum[100010],add[100010];
int L[100010],R[100010];//每一段的左右端点 
int pos[100010];//每个位置属于哪一段
int n,m,t;

void change(int l,int r,ll d){
	int p=pos[l],q=pos[r];
	if(p==q){
		for(int i=l;i<=r;i++) a[i]+=d;
		sum[p]+=d*(r-l+1);
	}
	else{
		for(int i=p+1;i<=q-1;i++) add[i]+=d;
		for(int i=l;i<=R[p];i++) a[i]+=d;
		sum[p]+=d*(R[p]-l+1);
		for(int i=L[q];i<=r;i++) a[i]+=d;
		sum[q]+=d*(r-L[q]+1);
	}
} 

ll query(int l,int r){
	int p=pos[l],q=pos[r];
	ll ans=0;
	if(p==q){
		for(int i=l;i<=r;i++) ans+=a[i];
		ans+=add[p]*(r-l+1);
	}
	else{
		for(int i=p+1;i<=q-1;i++) ans+=sum[i]+add[i]*(R[i]-L[i]+1);
		for(int i=l;i<=R[p];i++) ans+=a[i];
		ans+=add[p]*(R[p]-l+1);
		for(int i=L[q];i<=r;i++) ans+=a[i];
		ans+=add[q]*(r-L[q]+1); 
	}
	return ans;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	t=sqrt(n);
	for(int i=1;i<=t;i++){
		L[i]=(i-1)*sqrt(n)+1;
		R[i]=i*sqrt(n);
	}
	if(R[t]<n){
		t++;
		L[t]=R[t-1]+1;
		R[t]=n;
	}
	for(int i=1;i<=t;i++){
		for(int j=L[i];j<=R[i];j++){
			pos[j]=i;
			sum[i]+=a[j];
		}
	}
	while(m--){
		int op,l,r,d;
		cin>>op>>l>>r;
		if(op==1){
			cin>>d;
			change(l,r,d);
		}
		else cout<<query(l,r)<<endl;
	}
	return 0;
}
