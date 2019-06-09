#include<bits/stdc++.h>
using namespace std;
const int SIZE=100009;
struct Edge{
	int to,next;
}e[SIZE*2],ec[SIZE*2];
int head[SIZE],dfn[SIZE],low[SIZE],num,tot,dcc,c[SIZE];
int headc[SIZE],totc;
bool bridge[SIZE];
int n,m;

void add(int x,int y){
	e[++tot].to=y;
	e[tot].next=head[x];
	head[x]=tot;
}

void add_c(int x,int y){
	ec[++totc].to=y;
	ec[totc].next=head[x];
	headc[x]=totc;
}

void tarjan(int x,int in_edge){
	dfn[x]=low[x]=++num;
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].to;
		if(!dfn[y]){
			tarjan(y,i);
			low[x]=min(low[x],low[y]);
			if(dfn[x]<low[y]) bridge[i]=bridge[i^1]=1;
		}
		else if(i!=(in_edge^1)){
			low[x]=min(low[x],dfn[y]);
		}
	}
}

void dfs(int x){
	c[x]=dcc;
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].to;
		if(c[y]||bridge[i]) continue;
		dfs(y);
	}
}

int main(){
	cin>>n>>m;
	tot=1;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		add(x,y),add(y,x);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]) tarjan(i,0);
	}
	cout<<"桥："<<endl;
	for(int i=2;i<tot;i+=2){
		if(bridge[i]) cout<<e[i].to<<" "<<e[i^1].to<<endl;
	}
	for(int i=1;i<=n;i++){
		if(!c[i]) dcc++,dfs(i);
	}
	for(int i=1;i<=n;i++){
		printf("%d属于第%d个dcc\n",i,c[i]);
	}
	
	
	
	//缩点
	totc=1;
	for(int i=2;i<=tot;i++){
		int x=e[i^1].to,y=e[i].to;
		if(c[x]==c[y]) continue;
		add_c(c[x],c[y]);
	}
	printf("缩点后共%d个节点，%d条边\n",dcc,totc/2);
	for(int i=2;i<totc;i+=2){
		cout<<ec[i^1].to<<" "<<ec[i].to<<endl;
	}
	return 0;
}
