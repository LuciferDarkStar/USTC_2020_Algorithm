#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node
{
    int data;
    int p;
    int rank;
};
typedef struct node Link;
Link x[5000000];
void Make(int i)
{
    x[i].data=i;
    x[i].p=i;
    x[i].rank=0;
}
int Find(int i)
{
    if(x[i].p!=i)
        x[i].p=Find(x[i].p);
    return x[i].p;
}
void L(int i,int j)
{
    if(x[i].rank>x[j].rank)
        x[j].p=i;
    else
    {
        x[i].p=j;
        if(x[i].rank==x[j].rank)
            x[j].rank++;
    }

}
void Union(int i,int j)
{
    L(Find(i),Find(j));
}

int main()
{
    int n,m,k,i,a,b;
    scanf("%d",&n);
    scanf("%d",&k);
    scanf("%d",&m);
    for(i=0;i<n;i++)
        Make(i);
    for(i=0;i<m;i++)
    {
        scanf("%d",&a);
        scanf("%d",&b);
        Union(a,b);
    }
    for(i=0;i<k;i++)
    {
        scanf("%d",&a);
        scanf("%d",&b);
        if(Find(a)==Find(b))
            printf("1 ");
        else
            printf("0 ");
    }
}
