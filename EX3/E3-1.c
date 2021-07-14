#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct HashNode_Struct Node;
struct HashNode_Struct
{
    int x;
    int y;
};
Node node[10000];
int B[10000];
int BiSearch(int *b, int len, int w)
{
    int left = 0, right = len - 1;
    int mid;
    while (left <= right)
    {
        mid = left + (right-left)/2;
        if (b[mid] > w)
            right = mid - 1;
        else if (b[mid] < w)
            left = mid + 1;
        else    //找到了该元素，则直接返回
            return mid;
    }
    return left;//数组b中不存在该元素，则返回该元素应该插入的位置
}
int LIS(int n)
{
    int len = 1;
    B[0] = node[0].y;
    int i, pos = 0;
    for(i=1; i<n; ++i)
    {
        if(node[i].y > B[len-1]) //如果大于B中最大的元素，则直接插入到B数组末尾
        {
            B[len] = node[i].y;
            ++len;
        }
        else
        {
            pos = BiSearch(B, len, node[i].y); //二分查找需要插入的位置
            B[pos] = node[i].y;
        }
    }
    return len;
}

void swap(int i,int j)
{
    int a,b;
    a=node[i].x;
    b=node[i].y;
    node[i].x=node[j].x;
    node[i].y=node[j].y;
    node[j].x=a;
    node[j].y=b;
}
int Partition(int p,int r)
{
    int a=node[r].x;
    int b=node[r].y;
    int i=p-1;
    int j;
    for(j=p;j<=r-1;j++)
        if(node[j].x<a)
        {
            i++;
            swap(i,j);
        }
        else if(node[j].x==a)
        {
            if(node[j].y<=b)
            {
                i++;
                swap(i,j);
            }
        }
    swap(i+1,r);
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
    int n,i,a,b,k,j;
    scanf("%d",&n);
    int temp;
    for(i=0;i<n;i++)
    {
        scanf("%d",&node[i].x);
        scanf("%d",&node[i].y);
    }
    Quicksort(0,n-1);
    temp=LIS(n);
    printf("%d\n",temp);
}
