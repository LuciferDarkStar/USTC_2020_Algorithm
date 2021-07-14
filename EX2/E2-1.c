#include<stdio.h>
#include<stdlib.h>
#define LH 1
#define EH 0
#define RH -1
int temp;
typedef struct BiTNode
{
	int data;
	int bf;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
void R_Rotate(BiTree *P)
{
	BiTree L;
	L=(*P)->lchild;//L指向P的左子树根结点
	(*P)->lchild=L->rchild;//L的右子树挂接为P的左子树
	L->rchild=(*P);
	*P=L;//P指向新的根结点
}
void L_Rotate(BiTree *P)
{
	BiTree R;
	R=(*P)->rchild;//R指向P的右子树根结点
	(*P)->rchild=R->lchild;//R的左子树挂接为P的右子树
	R->lchild=(*P);
	*P=R;//P指向新的根结点
}
void LeftBalance(BiTree *T)
{
	BiTree L,Lr;
	L=(*T)->lchild;//L指向T的左子树根结点
	switch(L->bf)
	{
		//检查T的左子树平衡度，并作相应平衡处理
		case LH://新结点插入在T的左孩子的左子树上，要作单右旋处理
			(*T)->bf=L->bf=EH;
			R_Rotate(T);
			break;
		case RH://新结点插入在T的左孩子的右子树上，要作双旋处理
			Lr=L->rchild;
			switch(Lr->bf)//修改T及其左孩子的平衡因子
			{
				case LH:
					(*T)->bf=RH;
					L->bf=EH;
					break;
				case EH:
					(*T)->bf=L->bf=EH;
					break;
				case RH:
					(*T)->bf=EH;
					L->bf=LH;
					break;
			 }
			 Lr->bf=EH;
			 L_Rotate(&(*T)->lchild);
			 R_Rotate(T);
	 }
 }
//对以T为根节点的二叉树作右平衡旋转处理
void RightBalance(BiTree *T)
{
	BiTree R,Rl;
	R=(*T)->rchild;
	switch(R->bf)
	{
		//检查T的右子树平衡度，并作相应平衡处理
		case RH://新结点插入在T的左孩子的左子树上，要作单右旋处理
			(*T)->bf=R->bf=EH;
			L_Rotate(T);
			break;
		case LH://新结点插入在T的左孩子的右子树上，要作双旋处理
			Rl=R->lchild;
			switch(Rl->bf)//修改T及其左孩子的平衡因子
			{
				case RH:
					(*T)->bf=LH;
					R->bf=EH;
					break;
				case EH:
					(*T)->bf=R->bf=EH;
					break;
				case LH:
					(*T)->bf=EH;
					R->bf=RH;
					break;
			 }
			 Rl->bf=EH;
			 R_Rotate(&(*T)->rchild);
			 L_Rotate(T);
	 }
 }
 int InsertAVL(BiTree *T,int e,int *taller)
{
	if(!*T)
	{
		//插入新结点，树长高，置taller为1
		*T=(BiTree)malloc(sizeof(BiTNode));
		(*T)->data=e;
		(*T)->lchild=(*T)->rchild=NULL;
		(*T)->bf=EH;
		*taller=1;
	}
	else
	{
		if(e==(*T)->data)
		{
			//树中已存在和e相同关键字的结点则不再插入
			*taller=0;
			return 0;
		}
		if(e<(*T)->data)
		{
			//应继续在T的左子树中进行搜索
			if(!InsertAVL(&(*T)->lchild,e,taller))//未插入
				return 0;
			if(*taller)//已插入到T的左子树中且左子树“长高”
			{
				switch((*T)->bf)
				{
					case LH://原本左子树比右子树高，需要作左平衡处理
						LeftBalance(T);
						*taller=0;
						break;
					case EH://原本左右子树等高，现因左子树增高而树增高
						(*T)->bf=LH;
						*taller=1;
						break;
					case RH://原本右子树比左子树高，现左右子树等高
						(*T)->bf=EH;
						*taller=0;
						break;
				}
			 }
		}
	else	{
			//应继续在T的右子树中进行搜索
			if(!InsertAVL(&(*T)->rchild,e,taller))
				return 0;
			if(*taller)//已插入到T的右子树中且右子树“长高”
			{
				switch((*T)->bf)
				{
					case LH://原本左子树比右子树高，现左右子树等高
						(*T)->bf=EH;
						*taller=0;
						break;
					case EH://原本左右子树等高，现因右子树增高而树增高
						(*T)->bf=RH;
						*taller=1;
						break;
					case RH://原本右子树比左子树高，需要作右平衡处理
						RightBalance(T);
						*taller=0;
						break;
				}
			 }
		}
	}
	return 1;
 }

void Find(BiTree T,int a_id)
{
    BiTree t;;
    t=T;
    while(t!=NULL)
    {
        if(a_id==t->data)
        {
            printf("%d\n",t->data);
            break;
        }
        else
            if(a_id<t->data)
                t=t->lchild;
        else
            {
                temp=t->data;
                t=t->rchild;
            }
    }
    if(t==NULL)
        printf("%d\n",temp);
}
int main()
{
    char s[20];
    int a_id;
    int taller;
    BiTree T=NULL;
    scanf("%s",s);
    while(strcmp(s,"EXIT")!=0)
    {
        if(strcmp(s,"INSERT")==0)
        {
            scanf("%d",&a_id);
            InsertAVL(&T,a_id,&taller);
        }
        if(strcmp(s,"FIND")==0)
        {
            scanf("%d",&a_id);
            Find(T,a_id);
        }
        scanf("%s",s);
    }
    return 0;
}
