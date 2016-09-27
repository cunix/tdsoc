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
#define MAXSIZE 40 /* 存储空间初始分配量 */
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

/* 由串 S 复制得串 T */
Status StrCopy(String T,String S)
{
    int i;
    for(i=0; i<=S[0]; i++)
        T[i]=S[i];
    return OK;
}

/* 若 S 为空串,则返回 TRUE,否则返回 FALSE */
Status StrEmpty(String S)
{
    if(S[0]==0)
        return TRUE;
    else
        return FALSE;
}

/* 初始条件: 串 S 和 T 存在 */
/* 操作结果: 若 S>T,则返回值>0;若 S=T,则返回值=0;若 S<T,则返回值<0 */
int StrCompare(String S,String T)
{
    int i;
    for(i=1; i<=S[0]&&i<=T[0]; ++i)
        if(S[i]!=T[i])
            return S[i]-T[i];
    return S[0]-T[0];
}
/* 返回串的元素个数 */
int StrLength(String S)
{
    return S[0];
}
/* 初始条件:串 S 存在。操作结果:将 S 清为空串 */
Status ClearString(String S)
{
    S[0]=0;/* 令串长为零 */
    return OK;
}
/* 用 T 返回 S1 和 S2 联接而成的新串。若未截断，则返回 TRUE，否则 FALSE */
Status Concat(String T,String S1,String S2)
{
    int i;
    if(S1[0]+S2[0]<=MAXSIZE)
    {
        /* 未截断 */
        for(i=1; i<=S1[0]; i++)
            T[i]=S1[i];
        for(i=1; i<=S2[0]; i++)
            T[S1[0]+i]=S2[i];
        T[0]=S1[0]+S2[0];
        return TRUE;
    }
    else
    {
        /* 截断 S2 */
        for(i=1; i<=S1[0]; i++)
            T[i]=S1[i];
        for(i=1; i<=MAXSIZE-S1[0]; i++)
            T[S1[0]+i]=S2[i];
        T[0]=MAXSIZE;
        return FALSE;
    }
}
/* 用 Sub 返回串 S 的第 pos 个字符起长度为 len 的子串。 */
Status SubString(String Sub,String S,int pos,int len)
{
    int i;
    if(pos<1||pos>S[0]||len<0||len>S[0]-pos+1)
        return ERROR;
    for(i=1; i<=len; i++)
        Sub[i]=S[pos+i-1];
    Sub[0]=len;
    return OK;
}
/* 返回子串 T 在主串 S 中第 pos 个字符之后的位置。若不存在,则函数返回值为 0。 */
/* 其中,T 非空,1≤pos≤StrLength(S)。 */
int Index(String S, String T, int pos)
{
    int i = pos; /* i 用于主串 S 中当前位置下标值，若 pos 不为 1，则从 pos 位置开始匹配 */
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
/* T 为非空串。若主串 S 中第 pos 个字符之后存在与 T 相等的子串， */
/* 则返回第一个这样的子串在 S 中的位置，否则返回 0 */
int Index2(String S, String T, int pos)
{
    int n,m,i;
    String sub;
    if (pos > 0)
    {
        n = StrLength(S); /* 得到主串 S 的长度 */
        m = StrLength(T); /* 得到子串 T 的长度 */
        i = pos;
        while (i <= n-m+1)
        {
            SubString (sub, S, i, m); /* 取主串中第 i 个位置长度与 T 相等的子串给 sub */
            if (StrCompare(sub,T) != 0) /* 如果两串不相等 */
                ++i;
            else /* 如果两串相等 */
                return i; /* 则返回 i 值 */
        }
    }
    return 0; /* 若无子串与 T 相等，返回 0 */
}
/* 初始条件: 串 S 和 T 存在,1≤pos≤StrLength(S)+1 */
/* 操作结果: 在串 S 的第 pos 个字符之前插入串 T。完全插入返回 TRUE,部分插入返回 FALSE*/
Status StrInsert(String S,int pos,String T)
{
    int i;
    if(pos<1||pos>S[0]+1)
        return ERROR;
    if(S[0]+T[0]<=MAXSIZE)
    {
        /* 完全插入 */
        for(i=S[0]; i>=pos; i--)
            S[i+T[0]]=S[i];
        for(i=pos; i<pos+T[0]; i++)
            S[i]=T[i-pos+1];
        S[0]=S[0]+T[0];
        return TRUE;
    }
    else
    {
        /* 部分插入 */
        for(i=MAXSIZE; i<=pos; i--)
            S[i]=S[i-T[0]];
        for(i=pos; i<pos+T[0]; i++)
            S[i]=T[i-pos+1];
        S[0]=MAXSIZE;
        return FALSE;
    }
}
/* 初始条件: 串 S 存在,1≤pos≤StrLength(S)-len+1 */
/* 操作结果: 从串 S 中删除第 pos 个字符起长度为 len 的子串 */
Status StrDelete(String S,int pos,int len)
{
    int i;
    if(pos<1||pos>S[0]-len+1||len<0)
        return ERROR;
    for(i=pos+len; i<=S[0]; i++)
        S[i-len]=S[i];
    S[0]-=len;
    return OK;
}
/* 初始条件: 串 S,T 和 V 存在,T 是非空串（此函数与串的存储结构无关） */
/* 操作结果: 用 V 替换主串 S 中出现的所有与 T 相等的不重叠的子串 */
Status Replace(String S,String T,String V)
{
    int i=1; /* 从串 S 的第一个字符起查找串 T */
    if(StrEmpty(T)) /* T 是空串 */
        return ERROR;
    do
    {
        i=Index(S,T,i); /* 结果 i 为从上一个 i 之后找到的子串 T 的位置 */
        if(i) /* 串 S 中存在串 T */
        {
            StrDelete(S,i,StrLength(T)); /* 删除该串 T */
            StrInsert(S,i,V); /* 在原串 T 的位置插入串 V */
            i+=StrLength(V); /* 在插入的串 V 后面继续查找串 T */
        }
    }
    while(i);
    return OK;
}
/* 输出字符串 T */
void StrPrint(String T)
{
    int i;
    for(i=1; i<=T[0]; i++)
        printf("%c",T[i]);
    printf("\n");
}
int main()
{
    int i,j;
    Status k;
    char s;
    String t,s1,s2;
    printf("请输入串 s1: ");
    k=StrAssign(s1,"abcd");
    if(!k)
    {
        printf("串长超过 MAXSIZE(=%d)\n",MAXSIZE);
        exit(0);
    }
    printf("串长为%d 串空否？ %d(1:是 0:否)\n",StrLength(s1),StrEmpty(s1));
    StrCopy(s2,s1);
    printf("拷贝 s1 生成的串为: ");
    StrPrint(s2);
    printf("请输入串 s2: ");
    k=StrAssign(s2,"efghijk");
    if(!k)
    {
        printf("串长超过 MAXSIZE(%d)\n",MAXSIZE);
        exit(0);
    }
    i=StrCompare(s1,s2);
    if(i<0)
        s='<';
    else if(i==0)
        s='=';
    else
        s='>';
    printf("串 s1%c 串 s2\n",s);
    k=Concat(t,s1,s2);
    printf("串 s1 联接串 s2 得到的串 t 为: ");
    StrPrint(t);
    if(k==FALSE)
        printf("串 t 有截断\n");
    ClearString(s1);
    printf("清为空串后,串 s1 为: ");
    StrPrint(s1);
    printf("串长为%d 串空否？ %d(1:是 0:否)\n",StrLength(s1),StrEmpty(s1));
    printf("求串 t 的子串,请输入子串的起始位置,子串长度: ");
    i=2;
    j=3;
    printf("%d,%d \n",i,j);
    k=SubString(s2,t,i,j);
    if(k)
    {
        printf("子串 s2 为: ");
        StrPrint(s2);
    }
    printf("从串 t 的第 pos 个字符起,删除 len 个字符，请输入 pos,len: ");
    i=4;
    j=2;
    printf("%d,%d \n",i,j);
    StrDelete(t,i,j);
    printf("删除后的串 t 为: ");
    StrPrint(t);
    i=StrLength(s2)/2;
    StrInsert(s2,i,t);
    printf("在串 s2 的第%d 个字符之前插入串 t 后,串 s2 为:\n",i);
    StrPrint(s2);
    i=Index(s2,t,1);
    printf("s2 的第%d 个字母起和 t 第一次匹配\n",i);
    SubString(t,s2,1,1);
    printf("串 t 为： ");
    StrPrint(t);
    Concat(s1,t,t);
    printf("串 s1 为： ");
    StrPrint(s1);
    Replace(s2,t,s1);
    printf("用串 s1 取代串 s2 中和串 t 相同的不重叠的串后,串 s2 为: ");
    StrPrint(s2);
    return 0;
}
