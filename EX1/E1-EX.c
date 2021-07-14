#include<stdio.h>
int a[1000000];
int main()
{
    int n,k,i,j;
    int temp,flag;
    scanf("%d",&n);
    scanf("%d",&k);
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
    temp=a[0];
    flag=0;
    for(i=0;i<n-k+1;i++)
    {
        if(flag==i)
        {
            for(j=1;j<k;j++)
            {
                if(temp<=a[i+j])
                {
                    temp=a[i+j];
                    flag=i+j;
                }
            }
        }
        else
            if(flag<i)
            {
                temp=a[i];
                flag=i;
                for(j=1;j<k;j++)
                {
                    if(temp<=a[i+j])
                    {
                        temp=a[i+j];
                        flag=i+j;
                    }
                }
            }
        else
        {
            if(temp<=a[i+k-1])
            {
                temp=a[i+k-1];
                flag=i+k-1;
            }
        }
        printf("%d ",temp);
    }
    return 0;
}
