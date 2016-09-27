#define MAXSIZE 20
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef int ElemType;
typedef struct
{
    ElemType data[MAXSIZE];
    int length;
} SqList;

/* Get Element From SqList*/
Status GetElem(SqList L,int i,ElemType *e)
{
    if(L.length==0||i<1||i>L.length)
        return ERROR;
    *e=L.data[i-1];
    return OK;
}

/* Insert Element To SqList*/
Status ListInsert(SqList *L,int i,ElemType e)
{
    if(i<1||L->length==MAXSIZE||i>L->length+1)
        return ERROR;
    /*若插入的数据不在表尾*/
    if(i<=L->length)
    {
        int k;
        for(k=L->length-1;k=i-1; k--)
        {
            L->data[k+1]=L->data[k];
        }
    }
    L->data[i-1]=e;
    L->length++;
    return OK;
}


Status ListDelete(SqList *L,int i,ElemType *e){
  if(i>L->length||i<1)
    return ERROR;
  /*删除不在末尾*/
  *e=L->data[i];
  if(i<=L->length){
    int k=0;
    for(k=i;k<L->length;k++){
        L->data[k-1]=L->data[k];
    }
  }
  L->length--;
  return OK;

}

void main(){


}

