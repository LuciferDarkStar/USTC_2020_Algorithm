#include<stdio.h>
#include<stdlib.h>
int a[10000000];
int Partition(int p,int r)
{
    int x=a[r];
    int i=p-1;
    int j,temp;
    for(j=p;j<=r-1;j++)
        if(a[j]<=x)
        {
            i++;
            temp=a[i];
            a[i]=a[j];
            a[j]=temp;
        }
    temp=a[i+1];
    a[i+1]=a[r];
    a[r]=temp;
    return i+1;
}
int Rand_Partition(int p,int r)
{
    int temp,i;
    i=rand()%(r-p+1)+p;
    temp=a[r];
    a[r]=a[i];
    a[i]=temp;
    return Partition(p,r);
}
int Rand_Select(int p,int r,int i)
{
    int k,q;
    if(p==r)
        return a[p];
    q=Rand_Partition(p,r);
    k=q-p+1;
    if(i==k)
        return a[q];
    if(i<k)
        return Rand_Select(p,q-1,i);
    else
        return Rand_Select(q+1,r,i-k);
}
int main()
{
    int n,k,i;
    scanf("%d",&n);
    scanf("%d",&k);
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
    printf("%d\n",Rand_Select(0,n-1,k));
    return 0;
}
