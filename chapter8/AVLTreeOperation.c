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
/* 二叉树的二叉链表结点结构定义 */
typedef struct BiTNode /* 结点结构 */
{
    int data; /* 结点数据 */
    int bf; /* 结点的平衡因子 */
    struct BiTNode *lchild, *rchild; /* 左右孩子指针 */
} BiTNode, *BiTree;
/* 对以 p 为根的二叉排序树作右旋处理， */
/* 处理之后 p 指向新的树根结点，即旋转处理之前的左子树的根结点 */
void R_Rotate(BiTree *P)
{
    BiTree L;
    L=(*P)->lchild; /* L 指向 P 的左子树根结点 */
    (*P)->lchild=L->rchild; /* L 的右子树挂接为 P 的左子树 */
    L->rchild=(*P);
    *P=L; /* P 指向新的根结点 */
}
/* 对以 P 为根的二叉排序树作左旋处理， */
/* 处理之后 P 指向新的树根结点，即旋转处理之前的右子树的根结点 0 */
void L_Rotate(BiTree *P)
{
    BiTree R;
    R=(*P)->rchild; /* R 指向 P 的右子树根结点 */
    (*P)->rchild=R->lchild; /* R 的左子树挂接为 P 的右子树 */
    R->lchild=(*P);
    *P=R; /* P 指向新的根结点 */
}
#define LH +1 /* 左高 */
#define EH 0 /* 等高 */
#define RH -1 /* 右高 */
/* 对以指针 T 所指结点为根的二叉树作左平衡旋转处理 */
/* 本算法结束时，指针 T 指向新的根结点 */
void LeftBalance(BiTree *T)
{
    BiTree L,Lr;
    L=(*T)->lchild; /* L 指向 T 的左子树根结点 */
    switch(L->bf)
    {
    /* 检查 T 的左子树的平衡度，并作相应平衡处理 */
    case LH: /* 新结点插入在 T 的左孩子的左子树上，要作单右旋处理 */
        (*T)->bf=L->bf=EH;
        R_Rotate(T);
        break;
    case RH: /* 新结点插入在 T 的左孩子的右子树上，要作双旋处理 */
        Lr=L->rchild; /* Lr 指向 T 的左孩子的右子树根 */
        switch(Lr->bf)
        {
        /* 修改 T 及其左孩子的平衡因子 */
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
        L_Rotate(&(*T)->lchild); /* 对 T 的左子树作左旋平衡处理 */
        R_Rotate(T); /* 对 T 作右旋平衡处理 */
    }
}
/* 对以指针 T 所指结点为根的二叉树作右平衡旋转处理， */
/* 本算法结束时，指针 T 指向新的根结点 */
void RightBalance(BiTree *T)
{
    BiTree R,Rl;
    R=(*T)->rchild; /* R 指向 T 的右子树根结点 */
    switch(R->bf)
    {
    /* 检查 T 的右子树的平衡度，并作相应平衡处理 */
    case RH: /* 新结点插入在 T 的右孩子的右子树上，要作单左旋处理 */
        (*T)->bf=R->bf=EH;
        L_Rotate(T);
        break;
    case LH: /* 新结点插入在 T 的右孩子的左子树上，要作双旋处理 */
        Rl=R->lchild; /* Rl 指向 T 的右孩子的左子树根 */
        switch(Rl->bf)
        {
        /* 修改 T 及其右孩子的平衡因子 */
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
        R_Rotate(&(*T)->rchild); /* 对 T 的右子树作右旋平衡处理 */
        L_Rotate(T); /* 对 T 作左旋平衡处理 */
    }
}
/* 若在平衡的二叉排序树 T 中不存在和 e 有相同关键字的结点，则插入一个 */
/* 数据元素为 e 的新结点，并返回 1，否则返回 0。若因插入而使二叉排序树 */
/* 失去平衡，则作平衡旋转处理，布尔变量 taller 反映 T 长高与否。 */
Status InsertAVL(BiTree *T,int e,Status *taller)
{
    if(!*T)
    {
        /* 插入新结点，树“长高”，置 taller 为 TRUE */
        *T=(BiTree)malloc(sizeof(BiTNode));
        (*T)->data=e;
        (*T)->lchild=(*T)->rchild=NULL;
        (*T)->bf=EH;
        *taller=TRUE;
    }
    else
    {
        if (e==(*T)->data)
        {
            /* 树中已存在和 e 有相同关键字的结点则不再插入 */
            *taller=FALSE;
            return FALSE;
        }
        if (e<(*T)->data)
        {
            /* 应继续在 T 的左子树中进行搜索 */
            if(!InsertAVL(&(*T)->lchild,e,taller)) /* 未插入 */
                return FALSE;
            if(taller) /* 已插入到 T 的左子树中且左子树“长高” */
                switch((*T)->bf) /* 检查 T 的平衡度 */
                {
                case LH: /* 原本左子树比右子树高，需要作左平衡处理 */
                    LeftBalance(T);
                    *taller=FALSE;
                    break;
                case EH: /* 原本左、右子树等高，现因左子树增高而使树增高 */
                    (*T)->bf=LH;
                    *taller=TRUE;
                    break;
                case RH: /* 原本右子树比左子树高，现左、右子树等高 */
                    (*T)->bf=EH;
                    *taller=FALSE;
                    break;
                }
        }
        else
        {
            /* 应继续在 T 的右子树中进行搜索 */
            if(!InsertAVL(&(*T)->rchild,e,taller)) /* 未插入 */
                return FALSE;
            if(*taller) /* 已插入到 T 的右子树且右子树“长高” */
                switch((*T)->bf) /* 检查 T 的平衡度 */
                {
                case LH: /* 原本左子树比右子树高，现左、右子树等高 */
                    (*T)->bf=EH;
                    *taller=FALSE;
                    break;
                case EH: /* 原本左、右子树等高，现因右子树增高而使树增高 */
                    (*T)->bf=RH;
                    *taller=TRUE;
                    break;
                case RH: /* 原本右子树比左子树高，需要作右平衡处理 */
                    RightBalance(T);
                    *taller=FALSE;
                    break;
                }
        }
    }
    return TRUE;
}
int main(void)
{
    int i;
    int a[10]= {3,2,1,4,5,6,7,10,9,8};
    BiTree T=NULL;
    Status taller;
    for(i=0; i<10; i++)
    {
        InsertAVL(&T,a[i],&taller);
    }
    printf("本样例建议断点跟踪查看平衡二叉树结构");
    return 0;
}
