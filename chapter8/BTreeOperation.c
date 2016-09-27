#include "stdio.h"
#include "stdlib.h"
#include "io.h"
#include "math.h"
#include "time.h"
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100 /* 存储空间初始分配量 */
#define m 3 /* B 树的阶，暂设为 3 */
#define N 17 /* 数据元素个数 */
#define MAX 5 /* 字符串最大长度+1 */
typedef int Status; /* Status 是函数的类型,其值是函数结果状态代码，如 OK 等 */
typedef struct BTNode
{
    int keynum; /* 结点中关键字个数，即结点的大小 */
    struct BTNode *parent; /* 指向双亲结点 */
    struct Node /* 结点向量类型 */
    {
        int key; /* 关键字向量 */
        struct BTNode *ptr; /* 子树指针向量 */
        int recptr; /* 记录指针向量 */
    } node[m+1]; /* key,recptr 的 0 号单元未用 */
} BTNode,*BTree; /* B 树结点和 B 树的类型 */
typedef struct
{
    BTNode *pt; /* 指向找到的结点 */
    int i; /* 1..m，在结点中的关键字序号 */
    int tag; /* 1:查找成功， O:查找失败 */
} Result; /* B 树的查找结果类型 */
/* 在 p->node[1..keynum].key 中查找 i,使得 p->node[i].key≤K＜p->node[i+1].key */
int Search(BTree p, int K)
{
    int i=0,j;
    for(j=1; j<=p->keynum; j++)
        if(p->node[j].key<=K)
            i=j;
    return i;
}
/* 在 m 阶 B 树 T 上查找关键字 K，返回结果(pt,i,tag)。若查找成功，则特征值 */
/* tag=1，指针 pt 所指结点中第 i 个关键字等于 K；否则特征值 tag=0，等于 K 的 */
/* 关键字应插入在指针 Pt 所指结点中第 i 和第 i+1 个关键字之间。 */
Result SearchBTree(BTree T, int K)
{
    BTree p=T,q=NULL; /* 初始化， p 指向待查结点， q 指向 p 的双亲 */
    Status found=FALSE;
    int i=0;
    Result r;
    while(p&&!found)
    {
        i=Search(p,K); /* p->node[i].key≤K<p->node[i+1].key */
        if(i>0&&p->node[i].key==K) /* 找到待查关键字 */
            found=TRUE;
        else
        {
            q=p;
            p=p->node[i].ptr;
        }
    }
    r.i=i;
    if(found) /* 查找成功 */
    {
        r.pt=p;
        r.tag=1;
    }
    else /* 查找不成功，返回 K 的插入位置信息 */
    {
        r.pt=q;
        r.tag=0;
    }
    return r;
}
/* 将 r->key、 r 和 ap 分别插入到 q->key[i+1]、 q->recptr[i+1]和 q->ptr[i+1]中 */
void Insert(BTree *q,int i,int key,BTree ap)
{
    int j;
    for(j=(*q)->keynum; j>i; j--) /* 空出(*q)->node[i+1] */
        (*q)->node[j+1]=(*q)->node[j];
    (*q)->node[i+1].key=key;
    (*q)->node[i+1].ptr=ap;
    (*q)->node[i+1].recptr=key;
    (*q)->keynum++;
}
/* 将结点 q 分裂成两个结点，前一半保留，后一半移入新生结点 ap */
void split(BTree *q,BTree *ap)
{
    int i,s=(m+1)/2;
    *ap=(BTree)malloc(sizeof(BTNode)); /* 生成新结点 ap */
    (*ap)->node[0].ptr=(*q)->node[s].ptr; /* 后一半移入 ap */
    for(i=s+1; i<=m; i++)
    {
        (*ap)->node[i-s]=(*q)->node[i];
        if((*ap)->node[i-s].ptr)
            (*ap)->node[i-s].ptr->parent=*ap;
    }
    (*ap)->keynum=m-s;
    (*ap)->parent=(*q)->parent;
    (*q)->keynum=s-1; /* q 的前一半保留，修改 keynum */
}
/* 生成含信息(T,r,ap)的新的根结点&T，原 T 和 ap 为子树指针 */
void NewRoot(BTree *T,int key,BTree ap)
{
    BTree p;
    p=(BTree)malloc(sizeof(BTNode));
    p->node[0].ptr=*T;
    *T=p;
    if((*T)->node[0].ptr)
        (*T)->node[0].ptr->parent=*T;
    (*T)->parent=NULL;
    (*T)->keynum=1;
    (*T)->node[1].key=key;
    (*T)->node[1].recptr=key;
    (*T)->node[1].ptr=ap;
    if((*T)->node[1].ptr)
        (*T)->node[1].ptr->parent=*T;
}
/* 在 m 阶 B 树 T 上结点*q 的 key[i]与 key[i+1]之间插入关键字 K 的指针 r。若引起 */
/* 结点过大,则沿双亲链进行必要的结点分裂调整,使 T 仍是 m 阶 B 树。 */
void InsertBTree(BTree *T,int key,BTree q,int i)
{
    BTree ap=NULL;
    Status finished=FALSE;
    int s;
    int rx;
    rx=key;
    while(q&&!finished)
    {
        Insert(&q,i,rx,ap); /* 将 r->key、 r 和 ap 分别插入到 q->key[i+1]、 q->recptr[i+1]和sdq->ptr[i+1]中 */
        if(q->keynum<m)
            finished=TRUE; /* 插入完成 */
        else
        {
            /* 分裂结点*q */
            s=(m+1)/2;
            rx=q->node[s].recptr;
            split(&q,&ap); /* 将 q->key[s+1..m],q->ptr[s..m]和 q->recptr[s+1..m]移入新结点*ap */
            q=q->parent;
            if(q)
                i=Search(q,key); /* 在双亲结点*q 中查找 rx->key 的插入位置 */
        }
    }
    if(!finished) /* T 是空树(参数 q 初值为 NULL)或根结点已分裂为结点*q 和*ap */
        NewRoot(T,rx,ap); /* 生成含信息(T,rx,ap)的新的根结点*T，原 T 和 ap 为子树指针*/
}
void print(BTNode c,int i) /* TraverseDSTable()调用的函数 */
{
    printf("(%d)",c.node[i].key);
}
int main()
{
    int r[N]= {22,16,41,58,8,11,12,16,17,22,23,31,41,52,58,59,61};
    BTree T=NULL;
    Result s;
    int i;
    for(i=0; i<N; i++)
    {
        s=SearchBTree(T,r[i]);
        if(!s.tag)
            InsertBTree(&T,r[i],s.pt,s.i);
    }
    printf("\n 请输入待查找记录的关键字: ");
    scanf("%d",&i);
    s=SearchBTree(T,i);
    if(s.tag)
        print(*(s.pt),s.i);
    else
        printf("没找到");
    printf("\n");
    return 0;
}
