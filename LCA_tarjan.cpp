#include<bits/stdc++.h>
using namespace std;
const int SIZE=500009;
struct Edge{
	int to,next;
}e[SIZE*2];
int deep[SIZE],fa[SIZE],tot,head[SIZE],tag[SIZE],lca[SIZE];
int n,m,s;
vector<int> ask[SIZE],ask_id[SIZE];

void add(int x,int y){
	e[++tot].to=y;
	e[tot].next=head[x];
	head[x]=tot;
}

int get(int x){
	return x==fa[x]?x:fa[x]=get(fa[x]);
}

void tarjan(int x){
	tag[x]=1;
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].to;
		if(tag[y]) continue;
		deep[y]=deep[x]+1;
		tarjan(y);
		fa[y]=x;
	}
	for(int i=0;i<ask[x].size();i++){
		if(tag[ask[x][i]]==2){
			lca[ask_id[x][i]]=get(ask[x][i]);
		}
	}
	tag[x]=2;
}

int main(){
	cin>>n>>m>>s;
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
	}
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		ask[x].push_back(y);
		ask[y].push_back(x);
		ask_id[x].push_back(i);
		ask_id[y].push_back(i);
	}
	tarjan(s);
	for(int i=1;i<=m;i++){
		printf("%d\n",lca[i]);
	}
	return 0;
}
