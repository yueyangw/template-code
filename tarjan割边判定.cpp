#include<bits/stdc++.h>
using namespace std;
const int SIZE=100009;
struct Edge{
	int to,next;
}e[SIZE*2];
int head[SIZE],dfn[SIZE],low[SIZE],n,m,tot,num;
bool bridge[SIZE*2];

void add(int x,int y){
	e[++tot].to=y;
	e[tot].next=head[x];
	head[x]=tot;
}

void tarjan(int x,int in_edge){
	dfn[x]=low[x]=++num;
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].to;
		if(!dfn[y]){
			tarjan(y,i);
			low[x]=min(low[x],low[y]);
			if(low[y]>dfn[x]) bridge[i]=bridge[i^1]=1;
		}
		else if(i!=(in_edge^1)){
			low[x]=min(low[x],dfn[y]);
		}
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
		if(!dfn[i]) tarjan(i,0);//因为不一定是连通图。 
	}
	
	for(int i=2;i<tot;i+=2){
		if(bridge[i]) cout<<e[i].to<<" "<<e[i^1].to<<endl;
	}
	return 0;
} 
