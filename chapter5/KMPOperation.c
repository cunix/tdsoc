#include "string.h"
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
typedef int Status; /* Status 是函数的类型,其值是函数结果状态代码，如 OK 等 */
typedef int ElemType; /* ElemType 类型根据实际情况而定，这里假设为 int */
typedef char String[MAXSIZE+1]; /* 0 号单元存放串的长度 */
/* 生成一个其值等于 chars 的串 T */
Status StrAssign(String T,char *chars)
{
    int i;
    if(strlen(chars)>MAXSIZE)
        return ERROR;
    else
    {
        T[0]=strlen(chars);
        for(i=1; i<=T[0]; i++)
            T[i]=*(chars+i-1);
        return OK;
    }
}
Status ClearString(String S)
{
    S[0]=0;/* 令串长为零 */
    return OK;
}
/* 输出字符串 T。 */
void StrPrint(String T)
{
    int i;
    for(i=1; i<=T[0]; i++)
        printf("%c",T[i]);
    printf("\n");
}
/* 输出 Next 数组值。 */
void NextPrint(int next[],int length)
{
    int i;
    for(i=1; i<=length; i++)
        printf("%d",next[i]);
    printf("\n");
}
/* 返回串的元素个数 */
int StrLength(String S)
{
    return S[0];
}
/* 朴素的模式匹配法 */
int Index(String S, String T, int pos)
{
    int i = pos; /* i 用于主串 S 中当前位置下标值，若 pos 不为 1，则从 pos 位置开始匹
配 */
    int j = 1; /* j 用于子串 T 中当前位置下标值 */
    while (i <= S[0] && j <= T[0]) /* 若 i 小于 S 的长度并且 j 小于 T 的长度时，循环继续 */
    {
        if (S[i] == T[j]) /* 两字母相等则继续 */
        {
            ++i;
            ++j;
        }
        else /* 指针后退重新开始匹配 */
        {
            i = i-j+2; /* i 退回到上次匹配首位的下一位 */
            j = 1; /* j 退回到子串 T 的首位 */
        }
    }
    if (j > T[0])
        return i-T[0];
    else
        return 0;
}
/* 通过计算返回子串 T 的 next 数组。 */
void get_next(String T, int *next)
{
    int i,j;
    i=1;
    j=0;
    next[1]=0;
    while (i<T[0]) /* 此处 T[0]表示串 T 的长度 */
    {
        if(j==0 || T[i]== T[j]) /* T[i]表示后缀的单个字符， T[j]表示前缀的单个字符 */
        {
            ++i;
            ++j;
            next[i] = j;
        }
        else
            j= next[j]; /* 若字符不相同，则 j 值回溯 */
    }
}
/* 返回子串 T 在主串 S 中第 pos 个字符之后的位置。若不存在，则函数返回值为 0。 */
/* T 非空， 1≤pos≤StrLength(S)。 */
int Index_KMP(String S, String T, int pos)
{
    int i = pos; /* i 用于主串 S 中当前位置下标值，若 pos 不为 1，则从 pos 位置开
始匹配 */
    int j = 1; /* j 用于子串 T 中当前位置下标值 */
    int next[255]; /* 定义一 next 数组 */
    get_next(T, next); /* 对串 T 作分析，得到 next 数组 */
    while (i <= S[0] && j <= T[0]) /* 若 i 小于 S 的长度并且 j 小于 T 的长度时，循环继续 */
    {
        if (j==0 || S[i] == T[j]) /* 两字母相等则继续，与朴素算法增加了 j=0 判断 */
        {
            ++i;
            ++j;
        }
        else /* 指针后退重新开始匹配 */
            j = next[j];/* j 退回合适的位置， i 值不变 */
    }
    if (j > T[0])
        return i-T[0];
    else
        return 0;
}
/* 求模式串 T 的 next 函数修正值并存入数组 nextval */
void get_nextval(String T, int *nextval)
{
    int i,j;
    i=1;
    j=0;
    nextval[1]=0;
    while (i<T[0]) /* 此处 T[0]表示串 T 的长度 */
    {
        if(j==0 || T[i]== T[j]) /* T[i]表示后缀的单个字符， T[j]表示前缀的单个字符 */
        {
            ++i;
            ++j;
            if (T[i]!=T[j]) /* 若当前字符与前缀字符不同 */
                nextval[i] = j; /* 则当前的 j 为 nextval 在 i 位置的值 */
            else
                nextval[i] = nextval[j]; /* 如果与前缀字符相同，则将前缀字符的 */
            /* nextval 值赋值给 nextval 在 i 位置的值
            */
        }
        else
            j= nextval[j]; /* 若字符不相同，则 j 值回溯 */
    }
}
int Index_KMP1(String S, String T, int pos)
{
    int i = pos; /* i 用于主串 S 中当前位置下标值，若 pos 不为 1，则从 pos 位置开
始匹配 */
    int j = 1; /* j 用于子串 T 中当前位置下标值 */
    int next[255]; /* 定义一 next 数组 */
    get_nextval(T, next); /* 对串 T 作分析，得到 next 数组 */
    while (i <= S[0] && j <= T[0]) /* 若 i 小于 S 的长度并且 j 小于 T 的长度时，循环继续 */
    {
        if (j==0 || S[i] == T[j]) /* 两字母相等则继续，与朴素算法增加了 j=0 判断 */
        {
            ++i;
            ++j;
        }
        else /* 指针后退重新开始匹配 */
            j = next[j];/* j 退回合适的位置， i 值不变 */
    }
    if (j > T[0])
        return i-T[0];
    else
        return 0;
}
int main()
{
    int i,*p;
    String s1,s2;
    StrAssign(s1,"abcdex");
    printf("子串为: ");
    StrPrint(s1);
    i=StrLength(s1);
    p=(int*)malloc((i+1)*sizeof(int));
    get_next(s1,p);
    printf("Next 为: ");
    NextPrint(p,StrLength(s1));
    printf("\n");
    StrAssign(s1,"abcabx");
    printf("子串为: ");
    StrPrint(s1);
    i=StrLength(s1);
    p=(int*)malloc((i+1)*sizeof(int));
    get_next(s1,p);
    printf("Next 为: ");
    NextPrint(p,StrLength(s1));
    printf("\n");
    StrAssign(s1,"ababaaaba");
    printf("子串为: ");
    StrPrint(s1);
    i=StrLength(s1);
    p=(int*)malloc((i+1)*sizeof(int));
    get_next(s1,p);
    printf("Next 为: ");
    NextPrint(p,StrLength(s1));
    printf("\n");
    StrAssign(s1,"aaaaaaaab");
    printf("子串为: ");
    StrPrint(s1);
    i=StrLength(s1);
    p=(int*)malloc((i+1)*sizeof(int));
    get_next(s1,p);
    printf("Next 为: ");
    NextPrint(p,StrLength(s1));
    printf("\n");
    StrAssign(s1,"ababaaaba");
    printf(" 子串为: ");
    StrPrint(s1);
    i=StrLength(s1);
    p=(int*)malloc((i+1)*sizeof(int));
    get_next(s1,p);
    printf(" Next 为: ");
    NextPrint(p,StrLength(s1));
    get_nextval(s1,p);
    printf("NextVal 为: ");
    NextPrint(p,StrLength(s1));
    printf("\n");
    StrAssign(s1,"aaaaaaaab");
    printf(" 子串为: ");
    StrPrint(s1);
    i=StrLength(s1);
    p=(int*)malloc((i+1)*sizeof(int));
    get_next(s1,p);
    printf(" Next 为: ");
    NextPrint(p,StrLength(s1));
    get_nextval(s1,p);
    printf("NextVal 为: ");
    NextPrint(p,StrLength(s1));
    printf("\n");
    StrAssign(s1,"00000000000000000000000000000000000000000000000001");
    printf("主串为: ");
    StrPrint(s1);
    StrAssign(s2,"0000000001");
    printf("子串为: ");
    StrPrint(s2);
    printf("\n");
    printf("主串和子串在第%d 个字符处首次匹配（朴素模式匹配算法） \n",Index(s1,s2,1));
    printf("主串和子串在第%d 个字符处首次匹配（ KMP 算法） \n",Index_KMP(s1,s2,1));
    printf("主串和子串在第%d个字符处首次匹配（ KMP改良算法） \n",Index_KMP1(s1,s2,1));
    return 0;
}
