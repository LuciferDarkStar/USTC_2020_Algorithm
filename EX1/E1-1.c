#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct TREE
{
    int id;
    int a_id;
    struct TREE *lchild,*rchild;
}*T,*Treetemp;
typedef struct TREE BiTNode;
void Insert(BiTNode *t,int id,int a_id)
{
    BiTNode *y;
    BiTNode *x;
    if(t->a_id==-1)
    {
        t->id=id;
        t->a_id=a_id;
    }
    else
    {
        x=(BiTNode*)malloc(sizeof(BiTNode));
        x->a_id=a_id;
        x->id=id;
        x->lchild=NULL;
        x->rchild=NULL;
        y=t;
        while(1)
        {

            if(x->a_id<y->a_id)
            {
                if(y->lchild==NULL)
                    break;
                else
                    y=y->lchild;
            }
            else
            {
                if(y->rchild==NULL)
                    break;
                else
                    y=y->rchild;
            }
        }
        if(x->a_id<y->a_id)
            y->lchild=x;
        else
            y->rchild=x;
    }
}
void Find(int a_id)
{
    BiTNode *t;
    t=T;
    while(t!=NULL)
    {
        if(a_id==t->a_id)
        {
            printf("%d\n",t->id);
            break;
        }
        else
            if(a_id<t->a_id)
                t=t->lchild;
        else
            t=t->rchild;
    }
    if(t==NULL)
        printf("-1\n");
}
int main()
{
    char s[20];
    int id,a_id;
    T=(BiTNode*)malloc(sizeof(BiTNode));
    T->id=-1;
    T->a_id=-1;
    T->lchild=NULL;
    T->rchild=NULL;
    scanf("%s",s);
    while(strcmp(s,"EXIT")!=0)
    {
        if(strcmp(s,"INSERT")==0)
        {
            scanf("%d",&id);
            scanf("%d",&a_id);
            Insert(T,id,a_id);
        }
        if(strcmp(s,"FIND")==0)
        {
            scanf("%d",&a_id);
            Find(a_id);
        }
        scanf("%s",s);
    }
    return 0;
}
