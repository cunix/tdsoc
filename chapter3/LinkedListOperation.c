#include "stdio.h"
#define MAXSIZE 20
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef int ElemType;
typedef struct Node
{
    ElemType data;
    struct Node *next;
} Node;
typedef struct Node *LinkList;

/*单链表存取*/
Status GetElem(LinkList L,int i,ElemType *e)
{
    int j=1;
    LinkList p;
    p=L->next;
    while(p&&j<i)
    {
        p=p->next;
        j++;
    }
    if(!p||j>i)
        return ERROR;
    *e=p->data;
    return OK;
}
/*单链表的插入*/
Status ListInsert(LinkList *L,int i,ElemType e)
{
    int j=0;
    LinkList p,s;
    p=*L;
    while(p&&j<i)
    {
        p=p->next;
        j++;
    }
    if(!p||j>i)
        return ERROR;
    s=(LinkList)malloc(sizeof(Node));
    s->data=e;
    s->next=p->next;
    p->next=s;
    return OK;
}

/*单链表的删除*/
Status ListDelete(LinkList *L,int i,ElemType *e)
{
    int j=0;
    LinkList p,s;
    p=*L;
    while(p->next&&j<i)
    {
        p=p->next;
        j++;
    }
    if(!(p->next)||j>i)
        return ERROR;
    s=p->next;
    p->next=s->next;
    *e=s;
    free(s);
    return OK;
}

/*单链表的整体创建(头部创建)*/
void CreateListHead(LinkList *L,int n){
    LinkList p;
    int i;
    srand(time(0));/*初始化随机种子*/
    *L=(LinkList)malloc(sizeof(Node));
    (*L)->next=NULL;
    for(i=0;i<n;i++){
       p=(LinkList)malloc(sizeof(Node));
       p->data=rand()%100+1;
       p->next=(*L)->next;
       (*L)->next=p;
    }

}

/*单链表的整体创建(尾部创建)*/
void CreateListTail(LinkList *L,int n){
    LinkList p,r;
    int i;
    srand(time(0));
    *L=(LinkList)malloc(sizeof(Node));
    r=*L;
    for(i=0;i<n;i++){
        p=(Node *)malloc(sizeof(Node));
        p->data=rand()*100%+1;
        r->next=p;
        r=p;
    }
    r->next=NULL;
}
/*单链表的整体清除*/
Status ClearList(LinkList *L){
    LinkList p,q;
    p=(*L)->next;
    while(p){
        q=p->next;
        free(q);
        p=q;
    }
    (*L)->next=NULL;
    return OK;
}







void main()
{
// char *string1="CharToStringPoninter";
// char chars[]="CharToStringPoninter";
// char *pc=chars;

// int i=0,j=0;
// for(i=0;i<10;i++)
//    printf("char=%c\n",*(string1+i));
// printf("-------------------\n");
// for(j=0;j<10;j++)
//    printf("char=%c\n",*(pc+j));

// char chars[]="CharToStringPoninter",*p=chars;
// printf("address:%x",*(chars+1));
// printf("address:%x",*(p+1));

}
