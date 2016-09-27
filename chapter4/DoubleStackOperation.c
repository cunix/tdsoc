#include "stdio.h"
#include "stdlib.h"
#include "io.h"
#include "math.h"
#include "time.h"
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 /* 存储空间初始分配量 */
typedef int Status;
typedef int SElemType; /* SElemType 类型根据实际情况而定，这里假设为 int */
/* 两栈共享空间结构 */
typedef struct
{
    SElemType data[MAXSIZE];
    int top1; /* 栈 1 栈顶指针 */
    int top2; /* 栈 2 栈顶指针 */
} SqDoubleStack;

Status visit(SElemType c)
{
    printf("%d ",c);
    return OK;
}

/* 构造一个空栈 S */
Status InitStack(SqDoubleStack *S)
{
    S->top1=-1;
    S->top2=MAXSIZE;
    return OK;
}

/* 把 S 置为空栈 */
Status ClearStack(SqDoubleStack *S)
{
    S->top1=-1;
    S->top2=MAXSIZE;
    return OK;
}

/* 若栈 S 为空栈，则返回 TRUE，否则返回 FALSE */
Status StackEmpty(SqDoubleStack S)
{
    if (S.top1==-1 && S.top2==MAXSIZE)
        return TRUE;
    else
        return FALSE;
}

/* 返回 S 的元素个数，即栈的长度 */
int StackLength(SqDoubleStack S)
{
    return (S.top1+1)+(MAXSIZE-1-S.top2);
}

/* 插入元素 e 为新的栈顶元素 */
Status Push(SqDoubleStack *S,SElemType e,int stackNumber)
{
    if (S->top1+1==S->top2) /* 栈已满，不能再 push 新元素了 */
        return ERROR;
    if (stackNumber==1) /* 栈 1 有元素进栈 */
        S->data[++S->top1]=e; /* 若是栈 1 则先 top1+1 后给数组元素赋值。 */
    else if (stackNumber==2) /* 栈 2 有元素进栈 */
        S->data[--S->top2]=e; /* 若是栈 2 则先 top2-1 后给数组元素赋值。 */
    return OK;
}

/* 若栈不空，则删除 S 的栈顶元素，用 e 返回其值，并返回 OK；否则返回 ERROR */
Status Pop(SqDoubleStack *S,SElemType *e,int stackNumber)
{
    if (stackNumber==1)
    {
        if (S->top1==-1)
            return ERROR; /* 说明栈 1 已经是空栈，溢出 */
        *e=S->data[S->top1--]; /* 将栈 1 的栈顶元素出栈 */
    }
    else if (stackNumber==2)
    {
        if (S->top2==MAXSIZE)
            return ERROR; /* 说明栈 2 已经是空栈，溢出 */
        *e=S->data[S->top2++]; /* 将栈 2 的栈顶元素出栈 */
    }
    return OK;
}

Status StackTraverse(SqDoubleStack S)
{
    int i;
    i=0;
    while(i<S.top1)
    {
        visit(S.data[i++]);
    }
    i=S.top2;
    while(i<MAXSIZE)
    {
        visit(S.data[i++]);
    }
    printf("\n");
    return OK;
}

int main()
{
    int j;
    SqDoubleStack s;
    int e;
    if(InitStack(&s)==OK)
    {
        for(j=1; j<=5; j++)
            Push(&s,j,1);
        for(j=MAXSIZE; j>=MAXSIZE-2; j--)
            Push(&s,j,2);
    }
    printf("栈中元素依次为： ");
    StackTraverse(s);
    printf("当前栈中元素有： %d \n",StackLength(s));
    Pop(&s,&e,2);
    printf("弹出的栈顶元素 e=%d\n",e);
    printf("栈空否： %d(1:空 0:否)\n",StackEmpty(s));
    for(j=6; j<=MAXSIZE-2; j++)
        Push(&s,j,1);
    printf("栈中元素依次为： ");
    StackTraverse(s);
    printf("栈满否： %d(1:否 0:满)\n",Push(&s,100,1));
    ClearStack(&s);
    printf("清空栈后，栈空否： %d(1:空 0:否)\n",StackEmpty(s));
    return 0;
}
