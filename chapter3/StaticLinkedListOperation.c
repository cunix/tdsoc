#define MAXSIZE 1000
#define OK 1
typedef int ElemType;
typedef int Status;
typedef struct
{
    ElemType data;
    int cursor;
} Component,StaticLinkList[MAXSIZE];

Status InitList(StaticLinkList space)
{
    int i;
    for(i=0; i<MAXSIZE-1; i++)
        space[i].cursor=i+1;
    space[MAXSIZE-1].cursor=0;
    return OK;
}

/*若备用空间链表非空，则返回分配节点的下表，则返回0*/
int Malloc_SLL(StaticLinkList space){
  int i=space[0].cursor;
  if(space[0].cursor){
    space[0].cursor=space[i].cursor;
  }
}


void main()
{
    printf("|-----------------------------------------------|\n");
    printf("|----------------Compile Success----------------|\n");
    printf("|-----------------------------------------------|\n");
}
