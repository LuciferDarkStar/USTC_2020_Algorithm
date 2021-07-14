#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    int n,i,j,l,k,q;
    int A[200][200];
    int B[200][200];
    int a[200];
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
        A[i][i]=0;
        B[i][i]=a[i];
    }
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
            {
                B[i][j]=B[i][j-1]+a[j];
                printf("B[%d][%d]=%d\n",i,j,B[i][j]);
            }
    }

    for(l=2;l<=n;l++)
        for(i=0;i<=n-l+1;i++)
        {
            j=i+l-1;
            A[i][j]=2147483647;
            for(k=i;k<=j-1;k++)
            {
                q=A[i][k]+A[k+1][j]+B[i][j];
                if(q<A[i][j])
                    A[i][j]=q;
            }
        }
    printf("%d\n",A[0][n-1]);
    return 0;
}
