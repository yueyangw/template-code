#include<bits/stdc++.h>
using namespace std;
const int SIZE=100010;
struct Edge{
	int to,next;
}e[SIZE*2];
int head[SIZE],dfn[SIZE],low[SIZE],strck[SIZE],num,tot,sta,cnt;
int n,m,root;
bool cut[SIZE];
vector<int> dcc[SIZE];

Edge ec[SIZE*2];
int headc[SIZE],totc,tree_id[SIZE];

void add(int x,int y){
	e[++tot].to=y;
	e[tot].next=head[x];
	head[x]=tot;
}

void add_c(int x,int y){
	ec[++totc].to=y;
	ec[totc].next=headc[x];
	headc[x]=totc;
}

void tarjan(int x){
	strck[++sta]=x;
	dfn[x]=low[x]=++num;
	int flag=0;
	for(int i=head[x];i;i=e[i].next){
		int y=e[i].to;
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
			if(dfn[x]<=low[y]){
				flag++;
				if(x!=root||flag>1) cut[x]=1;
				int z;
				cnt++;
				do{
					z=strck[sta--];
					dcc[cnt].push_back(z);
				}while(z!=y);
				dcc[cnt].push_back(x);
			}
		}
		else low[x]=min(low[x],dfn[y]);
	}
}

int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		add(x,y),add(y,x);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]) root=i,tarjan(i);
	}
	printf("有%d个DCC\n",cnt);
	for(int i=1;i<=cnt;i++){
		printf("v-DCC #%d:",i);
		//cout<<dcc[i].size();
		for(int j=0;j<dcc[i].size();j++){
			printf("%d ",dcc[i][j]);
		}
		cout<<endl;
	}
	
	int treec=cnt;
	for(int i=1;i<=n;i++){
		if(cut[i]) tree_id[i]=++treec;
	}
	totc=1;
	for(int i=1;i<=cnt;i++){
		for(int j=0;j<dcc[i].size();j++){
			if(!cut[dcc[i][j]]) continue;
			add_c(i,tree_id[dcc[i][j]]);
			add_c(tree_id[dcc[i][j]],i);
		}
	}
	printf("缩点后共有%d个点，%d条边\n",treec,totc/2);
	printf("编号在[1,%d]的为原图v-DCC,编号大于%d的为原图割点。\n",cnt,cnt);
	for(int i=2;i<totc;i+=2){
		printf("%d %d\n",ec[i^1].to,ec[i].to);
	}
	return 0;
}
