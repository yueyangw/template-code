#include<bits/stdc++.h>
using namespace std;
//������� �鲢����������� �Ĺ���==
const int maxn=500000; 
int a[maxn],r[maxn],ans=0,n;//ans��Ϊȫ�ֱ�������¼����Ե������� 
void msort(int s,int t)
{
    if(s==t) return ;
    int mid=(s+t)/2;
    msort(s,mid);//���������������ݹ������
    msort(mid+1,t);//�����������J�J 
    int i=s,j=mid+1,k=s;
    while(i<=mid&&j<=t){
        if(a[i]<=a[j]){
        	r[k]=a[i];
        	k++,i++;
		}
        else{
            r[k]=a[j];
            k++,j++;
            ans+=mid-i+1;//ֻ����ᣬ�����Դ�==��
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
    msort(1,n);//��1��n��a��������
    printf("%d\n",ans);
    return 0;
}
