#include<bits/stdc++.h>
using namespace std;
int tot,head[500009],n,m,s,d[500009],f[500009][20],t,lg[500009];
struct Edge{
	int to,next;
}e[1000009];

void add(int x,int y){
	e[++tot].to=y;
	e[tot].next=head[x];
	head[x]=tot;
}

void dfs(int y,int x){
	d[y]=d[x]+1;
	f[y][0]=x;
	for(int i=1;(1<<i)<=d[y];i++) f[y][i]=f[f[y][i-1]][i-1];
	for(int i=head[y];i;i=e[i].next) if(e[i].to!=x) dfs(e[i].to,y);
}

int lca(int x,int y){
	if(d[x]>d[y]) swap(x,y);
	while(d[x]<d[y]) y=f[y][lg[d[y]-d[x]]-1];
	if(x==y) return x;
	for(int i=lg[d[x]]-1;i>=0;i--) if(f[x][i]!=f[y][i]) y=f[y][i],x=f[x][i];
	return f[x][0];
}

int main(){
	scanf("%d%d%d",&n,&m,&s);
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	for(int i=1;i<=n;i++) lg[i]=lg[i-1]+(1<<lg[i-1]==i);
	dfs(s,0);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		printf("%d\n",lca(x,y));
		//cout<<lca(x,y)<<endl;
	}
	return 0;
}
