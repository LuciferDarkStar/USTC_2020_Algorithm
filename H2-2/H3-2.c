#include<stdio.h>
int a[2500000][4];

void swap(int *a,int *b)
{
    int t[4],i;
    for(i=0;i<4;i++)
    {
        t[i]=a[i];
    }
    for(i=0;i<4;i++)
    {
        a[i]=b[i];
    }
    for(i=0;i<4;i++)
    {
        b[i]=t[i];
    }

}
int Compare(int r,int b[4])
{
    if(a[r][3]<b[3])
        return 1;
    if(a[r][3]==b[3]&&a[r][1]<b[1])
        return 1;
    if(a[r][3]==b[3]&&a[r][1]==b[1]&&a[r][0]<b[0])
        return 1;
    return 0;
}
int Partition(int p,int r)
{
    int x[4];
    int i=p-1;
    int j;
    x[0]=a[r][0];
    x[1]=a[r][1];
    x[2]=a[r][2];
    x[3]=a[r][3];
    for(j=p;j<=r-1;j++)
        if(Compare(j,x))
        {
            i++;
            swap(a[i],a[j]);
        }
    swap(a[i+1],a[r]);
    return i+1;
}

void Quicksort(int p,int r)
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
    int n,i,j;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i][0]);
        scanf("%d",&a[i][1]);
        scanf("%d",&a[i][2]);
        a[i][3]=a[i][1]+a[i][2];
    }
    Quicksort(0,n-1);
    for(i=n-1;i>=0;i--)
        printf("%d ",a[i][0]);
    return 0;
}
