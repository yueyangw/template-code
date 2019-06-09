#include<bits/stdc++.h>
using namespace std;

int n,m,s,dis[20009];
bool flag,vis[20009];

int cnt[20009];//»· 

struct Edge{
	int to,nxt,w;
}e[500009];
int head[20009],tot;

void add(int x,int y,int w){
	e[++tot].to=y;
	e[tot].nxt=head[x];
	e[tot].w=w;
	head[x]=tot;
}

bool spfa(int st){
	queue<int> q;
	q.push(st);
	dis[st]=0;
	cnt[st]=1;
	while(!q.empty()){
		int x=q.front();
		q.pop();
		vis[x]=0;
		for(int i=head[x];i;i=e[i].nxt){
			int y=e[i].to;
			if(dis[y]>dis[x]+e[i].w){
				dis[y]=dis[x]+e[i].w;
				cnt[y]=cnt[x]+1;
				if(cnt[y]>n){
					return 1;
				}//ÅÐ»· 
				if(!vis[y]){
					q.push(y);
					vis[y]=1;
				}
			}
		}
	}
	return 0;
}

int main(){
	int T;
	cin>>T;
	while(T--){
		tot=0;
		memset(head,0,sizeof(head));
		memset(e,0,sizeof(e));
		cin>>n>>m;
		for(int i=1;i<=m;i++){
			int x,y,w;
			cin>>x>>y>>w;
			add(x,y,w);
			if(w>=0) add(y,x,w);
		}
		memset(dis,0x3f,sizeof(dis));
		memset(vis,0,sizeof(vis));
		flag=0;
		if(spfa(1)) cout<<"YE5"<<endl;
		else cout<<"N0"<<endl;
	}
	return 0;
}
