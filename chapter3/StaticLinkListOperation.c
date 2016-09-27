#include "stdio.h"
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "io.h"
#include "math.h"
#include "time.h"
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* 存储空间初始分配量 */
typedef int Status;/* Status 是函数的类型,其值是函数结果状态代码，如 OK 等 */
typedef int ElemType;/* ElemType 类型根据实际情况而定，这里假设为 int */
Status visit(ElemType c)
{
    printf("%d ",c);
    return OK;
}
typedef struct Node
{
    ElemType data;
    struct Node *next;
} Node;
typedef struct Node *LinkList; /* 定义 LinkList */
/* 初始化顺序线性表 */
Status InitList(LinkList *L)
{
    *L=(LinkList)malloc(sizeof(Node)); /* 产生头结点,并使 L 指向此头结点 */
    if(!(*L)) /* 存储分配失败 */
        return ERROR;
    (*L)->next=NULL; /* 指针域为空 */
    return OK;
}
/* 初始条件：顺序线性表 L 已存在。操作结果：若 L 为空表，则返回 TRUE，否则返回 FALSE
*/
Status ListEmpty(LinkList L)
{
    if(L->next)
        return FALSE;
    else
        return TRUE;
}
/* 初始条件：顺序线性表 L 已存在。操作结果：将 L 重置为空表 */
Status ClearList(LinkList *L)
{
    LinkList p,q;
    p=(*L)->next; /* p 指向第一个结点 */
    while(p) /* 没到表尾 */
    {
        q=p->next;
        free(p);
        p=q;
    }
    (*L)->next=NULL; /* 头结点指针域为空 */
    return OK;
}
/* 初始条件：顺序线性表 L 已存在。操作结果：返回 L 中数据元素个数 */
int ListLength(LinkList L)
{
    int i=0;
    LinkList p=L->next; /* p 指向第一个结点 */
    while(p)
    {
        i++;
        p=p->next;
    }
    return i;
}
/* 初始条件：顺序线性表 L 已存在， 1≤i≤ListLength(L) */
/* 操作结果：用 e 返回 L 中第 i 个数据元素的值 */
Status GetElem(LinkList L,int i,ElemType *e)
{
    int j;
    LinkList p; /* 声明一结点 p */
    p = L->next; /* 让 p 指向链表 L 的第一个结点 */
    j = 1; /* j 为计数器 */
    while (p && j<i) /* p 不为空或者计数器 j 还没有等于 i 时，循环继续 */
    {
        p = p->next; /* 让 p 指向下一个结点 */
        ++j;
    }
    if ( !p || j>i )
        return ERROR; /* 第 i 个元素不存在 */
    *e = p->data; /* 取第 i 个元素的数据 */
    return OK;
}
/* 初始条件：顺序线性表 L 已存在 */
/* 操作结果：返回 L 中第 1 个与 e 满足关系的数据元素的位序。 */
/* 若这样的数据元素不存在，则返回值为 0 */
int LocateElem(LinkList L,ElemType e)
{
    int i=0;
    LinkList p=L->next;
    while(p)
    {
        i++;
        if(p->data==e) /* 找到这样的数据元素 */
            return i;
        p=p->next;
    }
    return 0;
}
/* 初始条件：顺序线性表 L 已存在,1≤i≤ListLength(L)， */
/* 操作结果：在 L 中第 i 个位置之前插入新的数据元素 e， L 的长度加 1 */
Status ListInsert(LinkList *L,int i,ElemType e)
{
    int j;
    LinkList p,s;
    p = *L;
    j = 1;
    while (p && j < i) /* 寻找第 i 个结点 */
    {
        p = p->next;
        ++j;
    }
    if (!p || j > i)
        return ERROR; /* 第 i 个元素不存在 */
    s = (LinkList)malloc(sizeof(Node)); /* 生成新结点(C 语言标准函数) */
    s->data = e;
    s->next = p->next; /* 将 p 的后继结点赋值给 s 的后继 */
    p->next = s; /* 将 s 赋值给 p 的后继 */
    return OK;
}
/* 初始条件：顺序线性表 L 已存在， 1≤i≤ListLength(L) */
/* 操作结果：删除 L 的第 i 个数据元素，并用 e 返回其值， L 的长度减 1 */
Status ListDelete(LinkList *L,int i,ElemType *e)
{
    int j;
    LinkList p,q;
    p = *L;
    j = 1;
    while (p->next && j < i) /* 遍历寻找第 i 个元素 */
    {
        p = p->next;
        ++j;
    }
    if (!(p->next) || j > i)
        return ERROR; /* 第 i 个元素不存在 */
    q = p->next;
    p->next = q->next; /* 将 q 的后继赋值给 p 的后继 */
    *e = q->data; /* 将 q 结点中的数据给 e */
    free(q); /* 让系统回收此结点，释放内存 */
    return OK;
}
/* 初始条件：顺序线性表 L 已存在 */
/* 操作结果：依次对 L 的每个数据元素输出 */
Status ListTraverse(LinkList L)
{
    LinkList p=L->next;
    while(p)
    {
        visit(p->data);
        p=p->next;
    }
    printf("\n");
    return OK;
}
/* 随机产生 n 个元素的值，建立带表头结点的单链线性表 L（头插法） */
void CreateListHead(LinkList *L, int n)
{
    LinkList p;
    int i;
    srand(time(0)); /* 初始化随机数种子 */
    *L = (LinkList)malloc(sizeof(Node));
    (*L)->next = NULL; /* 先建立一个带头结点的单链表 */
    for (i=0; i<n; i++)
    {
        p = (LinkList)malloc(sizeof(Node)); /* 生成新结点 */
        p->data = rand()%100+1; /* 随机生成 100 以内的数字 */
        p->next = (*L)->next;
        (*L)->next = p; /* 插入到表头 */
    }
}
/* 随机产生 n 个元素的值，建立带表头结点的单链线性表 L（尾插法） */
void CreateListTail(LinkList *L, int n)
{
    LinkList p,r;
    int i;
    srand(time(0)); /* 初始化随机数种子 */
    *L = (LinkList)malloc(sizeof(Node)); /* L 为整个线性表 */
    r=*L; /* r 为指向尾部的结点 */
    for (i=0; i<n; i++)
    {
        p = (Node *)malloc(sizeof(Node)); /* 生成新结点 */
        p->data = rand()%100+1; /* 随机生成 100 以内的数字 */
        r->next=p; /* 将表尾终端结点的指针指向新结点 */
        r = p; /* 将当前的新结点定义为表尾终端结点 */
    } r
    ->next = NULL; /* 表示当前链表结束 */
}
int main()
{
    LinkList L;
    ElemType e;
    Status i;
    int j,k;
    i=InitList(&L);
    printf("初始化 L 后： ListLength(L)=%d\n",ListLength(L));
    for(j=1; j<=5; j++)
        i=ListInsert(&L,1,j);
    printf("在 L 的表头依次插入 1～5 后： L.data=");
    ListTraverse(L);
    printf("ListLength(L)=%d \n",ListLength(L));
    i=ListEmpty(L);
    printf("L 是否空： i=%d(1:是 0:否)\n",i);
    i=ClearList(&L);
    printf("清空 L 后： ListLength(L)=%d\n",ListLength(L));
    i=ListEmpty(L);
    printf("L 是否空： i=%d(1:是 0:否)\n",i);
    for(j=1; j<=10; j++)
        ListInsert(&L,j,j);
    printf("在 L 的表尾依次插入 1～10 后： L.data=");
    ListTraverse(L);
    printf("ListLength(L)=%d \n",ListLength(L));
    ListInsert(&L,1,0);
    printf("在 L 的表头插入 0 后： L.data=");
    ListTraverse(L);
    printf("ListLength(L)=%d \n",ListLength(L));
    GetElem(L,5,&e);
    printf("第 5 个元素的值为： %d\n",e);
    for(j=3; j<=4; j++)
    {
        k=LocateElem(L,j);
        if(k)
            printf("第%d 个元素的值为%d\n",k,j);
        else
            printf("没有值为%d 的元素\n",j);
    }
    k=ListLength(L); /* k 为表长 */
    for(j=k+1; j>=k; j--)
    {
        i=ListDelete(&L,j,&e); /* 删除第 j 个数据 */
        if(i==ERROR)
            printf("删除第%d 个数据失败\n",j);
        else
            printf("删除第%d 个的元素值为： %d\n",j,e);
    }
    printf("依次输出 L 的元素： ");
    ListTraverse(L);
    j=5;
    ListDelete(&L,j,&e); /* 删除第 5 个数据 */
    printf("删除第%d 个的元素值为： %d\n",j,e);
    printf("依次输出 L 的元素： ");
    ListTraverse(L);
    i=ClearList(&L);
    printf("\n 清空 L 后： ListLength(L)=%d\n",ListLength(L));
    CreateListHead(&L,20);
    printf("整体创建 L 的元素(头插法)： ");
    ListTraverse(L);
    i=ClearList(&L);
    printf("\n 删除 L 后： ListLength(L)=%d\n",ListLength(L));
    CreateListTail(&L,20);
    printf("整体创建 L 的元素(尾插法)： ");
    ListTraverse(L);
    return 0;
}
