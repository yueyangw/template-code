#include<bits/stdc++.h>
using namespace std;
const int MAXN=100009;

int st[MAXN][22],lg[MAXN];
int n,m;

int query(int l,int r){
	int k=lg[r-l+1];
	return max(st[l][k],st[r-(1<<k)+1][k]);
}

int main(){
	cin>>n>>m;
	lg[0]=-1;
	for(int i=1;i<=n;i++) scanf("%d",&st[i][0]);
	for(int i=1;i<=n;i++) lg[i]=lg[i>>1]+1;
	for(int j=1;j<=20;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
		}
	}
	int l,r;
	for(int i=1;i<=m;i++){
		scanf("%d %d",&l,&r);
		printf("%d\n",query(l,r));
	}
	return 0;
}
