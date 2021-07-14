#include<stdio.h>
int a[1000];
int result[1000][2];
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
    int n,i,count,temp,j;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
    Quicksort(0,n-1);
    result[0][0]=a[0];
	result[0][1]=1;
	count=0;
	/*统计次数*/
	for(i=1;i<n;i++){
		if(a[i]==result[count][0]){
			result[count][1]++;
		}else{
			count++;
			result[count][0]=a[i];
			result[count][1]=1;
		}
	}
	/*对次数排序*/
    for(i=1;i<=count;i++)
    {
		for(j=i;j>0&&result[j][1]>result[j-1][1];j--)
        {
			temp=result[j][0];
			result[j][0]=result[j-1][0];
			result[j-1][0]=temp;

			temp=result[j][1];
			result[j][1]=result[j-1][1];
			result[j-1][1]=temp;
		}
	}
    for(i=0;i<=count;i++)
        printf("%d %d\n",result[i][0],result[i][1]);
	return 0;
}
