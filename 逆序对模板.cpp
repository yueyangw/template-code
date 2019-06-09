#include<bits/stdc++.h>
using namespace std;
//下面就是 归并排序求逆序对 的过程==
const int maxn=500000; 
int a[maxn],r[maxn],ans=0,n;//ans作为全局变量，记录逆序对的数量； 
void msort(int s,int t)
{
    if(s==t) return ;
    int mid=(s+t)/2;
    msort(s,mid);//→→→→→→→递归的体现
    msort(mid+1,t);//→→→→→↗↗ 
    int i=s,j=mid+1,k=s;
    while(i<=mid&&j<=t){
        if(a[i]<=a[j]){
        	r[k]=a[i];
        	k++,i++;
		}
        else{
            r[k]=a[j];
            k++,j++;
            ans+=mid-i+1;//只可意会，不可言传==；
        }
    }
    while(i<=mid)
        r[k]=a[i],k++,i++;
    while(j<=t)
        r[k]=a[j],k++,j++;
    for(int i=s;i<=t;i++)
        a[i]=r[i];
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) 
        scanf("%d",&a[i]);
    msort(1,n);//从1到n将a数组排序；
    printf("%d\n",ans);
    return 0;
}
