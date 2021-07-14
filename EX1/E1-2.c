#include<stdio.h>
#define N 1000000
int ans;
int a[N];
int temp[N];

void Merge(int s, int m, int e)
{
	int pb = 0;
	int p1 = s;
	int p2 = m + 1;
	while (p1 <= m && p2 <= e)
	{
		if (a[p1]<=a[p2])
		{
			temp[pb++] = a[p1++];
		}
		else
		{
			ans =(ans+ m - p1 + 1)%10000019;
			temp[pb++] = a[p2++];
		}
	}
	while (p1 <= m)
	{
		temp[pb++] = a[p1++];
	}
	while (p2 <= e)
	{
		temp[pb++] = a[p2++];
	}
	for (int i = 0; i < e - s + 1; i++)
	{
		a[s + i] = temp[i];
	}
}
void MergeSort(int s, int e)
{
	if (s < e)
	{
		int m = s + (e - s) / 2;
		MergeSort(s, m);
		MergeSort(m + 1, e);
		Merge(s, m, e);
	}
}
int main()
{
	int size;
	scanf("%d", &size);
	for (int i = 0; i < size; i++)
	{
		scanf("%d", &a[i]);
	}
	MergeSort(0, size - 1);
	printf("%d",ans%10000019);
	return 0;
}
