#include<stdio.h>
int a[100000];
int N;
int R;
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
    int i,j;
    int temp;
    int flag;
    int d;
    scanf("%d",&N);
    scanf("%d",&R);
    for(i=0;i<N;i++)
        scanf("%d",&a[i]);
    a[N]=1000000;
    Quicksort(0,N-1);
    flag=1;
    temp=0;
    d=-2147483648;
    for(i=0;i<N;)
    {
        if(a[i]<=d&&flag==1)
        {
            i++;
            continue;
        }
        if(a[i+1]-a[i]<=R)
        {
            if(flag==1)
            {
                j=i;
                i++;
                flag=0;
            }
            else
            {
                if(a[i+1]-a[j]<=R)
                {
                    i++;
                }
                else
                {
                    flag=1;
                    temp++;
                    d=a[i]+R;
                    i++;
                }
            }
        }
        else
        {
            temp++;
            d=a[i]+R;
            flag=1;
            i++;
        }
    }
    printf("%d\n",temp);
    return 0;
}
