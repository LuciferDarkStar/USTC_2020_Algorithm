#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define LL long long
typedef int bool;
#define true 1
#define false 0
const int INF=0x7FFFFFFF;

struct SBT
{
	int key, left, right, size;
} tree[2000000];

int root, top;

void left_rot(int *x)
{
	int y = tree[*x].right;
	tree[*x].right = tree[y].left;
	tree[y].left = *x;
	tree[y].size = tree[*x].size;//转上去的节点数量为先前此处节点的size
	tree[*x].size = tree[tree[*x].left].size + tree[tree[*x].right].size + 1;
	*x = y;
}

void right_rot(int *x)
{
	int y = tree[*x].left;
	tree[*x].left = tree[y].right;
	tree[y].right = *x;
	tree[y].size = tree[*x].size;
	tree[*x].size = tree[tree[*x].left].size + tree[tree[*x].right].size + 1;
	*x = y;
}

void maintain(int *x, bool flag)
{
	if (flag == false)//左边
	{
		if (tree[tree[tree[*x].left].left].size > tree[tree[*x].right].size)//左孩子的左子树大于右孩子
			right_rot(x);
		else if (tree[tree[tree[*x].left].right].size > tree[tree[*x].right].size)//右孩子的右子树大于右孩子
		{
			left_rot(&tree[*x].left);
			right_rot(x);
		}
		else return;
	}
	else //右边
	{
		if (tree[tree[tree[*x].right].right].size > tree[tree[*x].left].size)//右孩子的右子树大于左孩子
			left_rot(x);
		else if (tree[tree[tree[*x].right].left].size > tree[tree[*x].left].size)//右孩子的左子树大于左孩子
		{
			right_rot(&tree[*x].right);
			left_rot(x);
		}
		else return;
	}
	maintain(&tree[*x].left, false);
	maintain(&tree[*x].right, true);
	maintain(x, true);
	maintain(x, false);
}

/*
*insert没有合并相同的元素，如果出现相同的元素则把它放到右子树上，这样能保证求第k小数的时候对相同元素也能正确
*/
void insert(int *x, int key)
{
	if (*x == 0)
	{
		*x = ++top;
		tree[*x].left = tree[*x].right = 0;
		tree[*x].size = 1;
		tree[*x].key = key;
	}
	else
	{
		tree[*x].size++;
		if (key < tree[*x].key) insert(&tree[*x].left, key);
		else  insert(&tree[*x].right, key);//相同元素插入到右子树中
		maintain(x, key >= tree[*x].key);//每次插入把平衡操作压入栈中
	}
}

int del(int *p, int w)
{
	if (tree[*p].key == w || (tree[*p].left == 0 && w < tree[*p].key) || (tree[*p].right == 0 && w > tree[*p].key))
	{
		int delnum = tree[*p].key;
		if (tree[*p].left == 0 || tree[*p].right == 0) *p = tree[*p].left + tree[*p].right;
		else tree[*p].key = del(&tree[*p].left, INF);
		return delnum;
	}
	if (w < tree[*p].key) return del(&tree[*p].left, w);
	else return del(&tree[*p].right, w);
}

int  Delete(int *x, int key)
{
	int d_key;
	//if(!x) return 0;
	tree[*x].size--;
	if ((key == tree[*x].key) || (key < tree[*x].key && tree[*x].left == 0) ||
		(key > tree[*x].key && tree[*x].right == 0))
	{
		d_key = tree[*x].key;
		if (tree[*x].left && tree[*x].right)
		{
			tree[*x].key = Delete(&tree[*x].left, tree[*x].key + 1);
		}
		else
		{
			*x = tree[*x].left + tree[*x].right;
		}
	}
	else if (key > tree[*x].key)
		d_key = Delete(&tree[*x].right, key);
	else if (key < tree[*x].key)
		d_key = Delete(&tree[*x].left, key);
	return d_key;
}


int select(int *x, int k)//求第k小数
{
	int r = tree[tree[*x].left].size + 1;
	if (r == k) return tree[*x].key;
	else if (r < k) return select(&tree[*x].right, k - r);
	else return select(&tree[*x].left, k);
}

int rank(int *x, int key)//求key排第几
{
	if (key < tree[*x].key)
		return rank(&tree[*x].left, key);
	else if (key > tree[*x].key)
		return rank(&tree[*x].right, key) + tree[tree[*x].left].size + 1;
	return tree[tree[*x].left].size + 1;
}

int pred(int *x, int y, int key)//前驱 小于
{
	if (*x == 0) return y;
	if (tree[*x].key < key)
		return pred(&tree[*x].right, *x, key);
	else return pred(&tree[*x].left, y, key);
}

int succ(int *x, int y, int key)//后继 大于
{
	if (*x == 0) return y;
	if (tree[*x].key > key)
		return succ(&tree[*x].left, *x, key);
	else return succ(&tree[*x].right, y, key);
}


int main()
{

	char ch[2]={'\0'};
	int x, tmp, n, i;
	i = 0;
	root = top = 0;
	scanf("%d", &n);
	while (1)
	{
		scanf("%s", ch);
		scanf("%d", &x);
		switch (ch[0])
		{
		case 'I':
			insert(&root, x);
			break;
		case 'D':
			Delete(&root, x);
			break;
		case 'K':
			tmp = select(&root, x);
			printf("%d\n", tmp);
			break;
		}
		i = i + 1;
		if (i >= n)
			break;
	}
	return 0;
}
