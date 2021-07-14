#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define HASH_TABLE_MAX_SIZE 18260817
#define MAXN 10000010
typedef struct HashNode_Struct HashNode;

struct HashNode_Struct
{
    char *sKey;
    int nValue;
    HashNode* pNext;
};
int n;
HashNode* hashTable[HASH_TABLE_MAX_SIZE];
int hash_table_size;
void hash_table_init()
{
    hash_table_size = 0;
}


//string hash function
unsigned int hash_table_hash_str(const char* skey)
{
	int len = strlen(skey);
    unsigned int seed = 26;
    unsigned int val = 0;
    for (int i = 0; i < len; i++) {
        val = val * seed + skey[i];
    }
    return val;
}

void hash_table_insert(const char* skey)
{
    if(hash_table_size >= HASH_TABLE_MAX_SIZE)
    {
        printf("out of hash table memory!\n");
        return;
    }

    unsigned int pos = hash_table_hash_str(skey) % HASH_TABLE_MAX_SIZE;
    HashNode* pHead =  hashTable[pos];
    while(pHead)
    {
        if(strcmp(pHead->sKey, skey) == 0)
        {
            pHead->nValue++;
            return ;
        }
        pHead = pHead->pNext;
    }

    HashNode* pNewNode = (HashNode*)malloc(sizeof(HashNode));
    pNewNode->sKey = (char*)malloc(sizeof(char) * 6);
    strcpy(pNewNode->sKey, skey);
    pNewNode->nValue = 1;

    pNewNode->pNext = hashTable[pos];
    hashTable[pos] = pNewNode;


    hash_table_size++;
}
void hash_table_remove(const char* skey)
{
    unsigned int pos = hash_table_hash_str(skey) % HASH_TABLE_MAX_SIZE;
    if(hashTable[pos])
    {
        HashNode* pHead = hashTable[pos];
        HashNode* pLast = NULL;
        HashNode* pRemove = NULL;
        while(pHead)
        {
            if(strcmp(skey, pHead->sKey) == 0)
            {   if(pHead->nValue==1)
                {pRemove = pHead;
                hash_table_size--;
                break;}
                else{
                pHead->nValue--;
                return ;
                }
            }
            pLast = pHead;
            pHead = pHead->pNext;
        }
        if(pRemove)
        {
            if(pLast)
                pLast->pNext = pRemove->pNext;
            else
                hashTable[pos] = NULL;

            free(pRemove->sKey);
            free(pRemove);
        }
    }
}

char s[MAXN][10];
int main(){
	int number=0;
	int i,j;
	int k;
	scanf("%d",&n);
	scanf("%d",&k);
	for(i=0;i<n;i++)
	{
		scanf("%s",s[i]);
	}
	hash_table_init();
	int right,left1,left2;
	left1=0;
	left2=0;
	for(right=0;right<n;right++)
	{
		hash_table_insert(s[right]);
		while(hash_table_size>k)
		{   
			hash_table_remove(s[left1]);
			left1++;
		}
		int temp=left1;
		if(hash_table_size==k)
		{
			while(hash_table_size==k)
			{
				number++;
				hash_table_remove(s[temp]);
				temp++;
			}
			for(j=left1;j<temp;j++)
			{
				 hash_table_insert(s[j]);
			}
		}
	}
	printf("%d\n",number);
	return 0;
}
