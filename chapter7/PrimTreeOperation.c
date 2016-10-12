#include "stdio.h"
#include "stdlib.h"
#include "io.h"
#include "math.h"
#include "time.h"
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXEDGE 20
#define MAXVEX 20
#define INFINITY 65535
typedef int Status; /* Status 是函数的类型,其值是函数结果状态代码，如 OK 等 */
typedef struct
{
    int arc[MAXVEX][MAXVEX];
    int numVertexes, numEdges;
} MGraph;
void CreateMGraph(MGraph *G)/* 构件图 */
{
    int i, j;
    /* printf("请输入边数和顶点数:"); */
    G->numEdges=15;
    G->numVertexes=9;
    for (i = 0; i < G->numVertexes; i++)/* 初始化图 */
    {
        for ( j = 0; j < G->numVertexes; j++)
        {
            if (i==j)
                G->arc[i][j]=0;
            else
                G->arc[i][j] = G->arc[j][i] = INFINITY;
        }
    }
    G->arc[0][1]=10;
    G->arc[0][5]=11;
    G->arc[1][2]=18;
    G->arc[1][8]=12;
    G->arc[1][6]=16;
    G->arc[2][8]=8;
    G->arc[2][3]=22;
    G->arc[3][8]=21;
    G->arc[3][6]=24;
    G->arc[3][7]=16;
    G->arc[3][4]=20;
    G->arc[4][7]=7;
    G->arc[4][5]=26;
    G->arc[5][6]=17;
    G->arc[6][7]=19;
    for(i = 0; i < G->numVertexes; i++)
    {
        for(j = i; j < G->numVertexes; j++)
        {
            G->arc[j][i] =G->arc[i][j];
        }
    }
}
/* Prim 算法生成最小生成树 */
void MiniSpanTree_Prim(MGraph G)
{
    int min, i, j, k;
    int adjvex[MAXVEX];     /* 保存相关顶点下标 */
    int lowcost[MAXVEX];    /* 保存相关顶点间边的权值 */
    lowcost[0] = 0;         /* 初始化第一个权值为 0，即 v0 加入生成树 */
                            /* lowcost 的值为 0，在这里就是此下标的顶点已经加入生成树 */
    adjvex[0] = 0;          /* 初始化第一个顶点下标为 0 */
    for(i = 1; i < G.numVertexes; i++) /* 循环除下标为 0 外的全部顶点 */
    {
        lowcost[i] = G.arc[0][i]; /* 将 v0 顶点与之有边的权值存入数组 */
        adjvex[i] = 0;            /* 初始化都为 v0 的下标 */
    }

    for(i = 1; i < G.numVertexes; i++)
    {
        min = INFINITY; /* 初始化最小权值为∞， */
                        /* 通常设置为不可能的大数字如 32767、65535 等 */
        j = 1;
        k = 0;
        while(j < G.numVertexes) /* 循环全部顶点 */
        {
            if(lowcost[j]!=0 && lowcost[j] < min)/* 如果权值不为 0 且权值小于 min */
            {
                min = lowcost[j];                /* 则让当前权值成为最小值 */
                k = j;                           /* 将当前最小值的下标存入 k */
            }
            j++;
        }
        printf("(%d, %d)\n", adjvex[k], k); /* 打印当前顶点边中权值最小的边 */
        lowcost[k] = 0;                     /* 将当前顶点的权值设置为 0,表示此顶点已经完成任务 */
        for(j = 1; j < G.numVertexes; j++)  /* 循环所有顶点 */
        {
            if(lowcost[j]!=0 && G.arc[k][j] < lowcost[j])
            {
                                            /* 如果下标为 k 顶点各边权值小于此前这些顶点未被加入生成树权值 */
                lowcost[j] = G.arc[k][j];   /* 将较小的权值存入 lowcost 相应位置 */
                adjvex[j] = k;              /* 将下标为 k 的顶点存入 adjvex */
            }
        }
    }
}
int main(void)
{
    MGraph G;
    CreateMGraph(&G);
    MiniSpanTree_Prim(G);
    return 0;
}
