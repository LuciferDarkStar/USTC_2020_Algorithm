#include<stdio.h>
int a[10000000];
int b[10000000];
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
int Quicksort(int p,int r)
{
    int q;
    if(p<r)
    {
        q=Partition(p,r);
        Quicksort(p,q-1);
        Quicksort(q+1,r);
    }
}
int main()
{
    int n,i;
    int x;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
    Quicksort(0,n-1);
    for(i=0;i<n-1;i++)
        b[i]=a[i+1]-a[i];
    x=b[0];
    for(i=1;i<n-1;i++)
    {
        if(b[i]>x)
            x=b[i];
    }
    printf("%d",x);
}
