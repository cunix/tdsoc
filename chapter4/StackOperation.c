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
/* 顺序栈结构 */
typedef struct
{
    SElemType data[MAXSIZE];
    int top; /* 用于栈顶指针 */
} SqStack;

/*查看栈元素*/
Status visit(SElemType c)
{
    printf("%d ",c);
    return OK;
}

/* 插入元素 e 为新的栈顶元素 */
Status Push(SqStack *S,SElemType e)
{
    if(S->top == MAXSIZE -1) /* 栈满 */
        return ERROR;
    S->top++; /* 栈顶指针增加一 */
    S->data[S->top]=e; /* 将新插入元素赋值给栈顶空间 */
    return OK;
}

/* 若栈不空，则删除 S 的栈顶元素，用 e 返回其值，并返回 OK；否则返回 ERROR */
Status Pop(SqStack *S,SElemType *e)
{
    if(S->top==-1)
        return ERROR;
    *e=S->data[S->top]; /* 将要删除的栈顶元素赋值给 e */
    S->top--; /* 栈顶指针减一 */
    return OK;
}


/* 构造一个空栈 S */
Status InitStack(SqStack *S)
{
    /* S.data=(SElemType *)malloc(MAXSIZE*sizeof(SElemType)); */
    S->top=-1;
    return OK;
}

/* 把 S 置为空栈 */
Status ClearStack(SqStack *S)
{
    S->top=-1;
    return OK;
}

/* 若栈 S 为空栈，则返回 TRUE，否则返回 FALSE */
Status StackEmpty(SqStack S)
{
    if (S.top==-1)
        return TRUE;
    else
        return FALSE;
}

/* 返回 S 的元素个数，即栈的长度 */
int StackLength(SqStack S)
{
    return S.top+1;
}

/* 若栈不空，则用 e 返回 S 的栈顶元素，并返回 OK；否则返回 ERROR */
Status GetTop(SqStack S,SElemType *e)
{
    if (S.top==-1)
        return ERROR;
    else
        *e=S.data[S.top];
    return OK;
}



/* 从栈底到栈顶依次对栈中每个元素显示 */
Status StackTraverse(SqStack S)
{
    int i;
    i=0;
    while(i<=S.top)
    {
        visit(S.data[i++]);
    }
    printf("\n");
    return OK;
}

int main()
{
    int j;
    SqStack s;
    int e;
    if(InitStack(&s)==OK)
        for(j=1; j<=10; j++)
            Push(&s,j);
    printf("栈中元素依次为： ");
    StackTraverse(s);
    Pop(&s,&e);
    printf("弹出的栈顶元素 e=%d\n",e);
    printf("栈空否： %d(1:空 0:否)\n",StackEmpty(s));
    GetTop(s,&e);
    printf("栈顶元素 e=%d 栈的长度为%d\n",e,StackLength(s));
    ClearStack(&s);
    printf("清空栈后，栈空否： %d(1:空 0:否)\n",StackEmpty(s));
    return 0;
}
