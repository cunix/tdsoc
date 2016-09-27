#include "stdio.h"

void main(){
    algorithm3();
}

void algorithm1(){
    long i,sum=0;
    for(i=0;i<10001;i++){
        sum+=i;
    }
    printf("%d",sum);
}

void algorithm2(){
    long sum,s=1,e=10000;
    sum=(s+e)*e/2;
    printf("%d",sum);
}


void algorithm3(){
  int i,j,x=0,sum=0;
  for(i=1;i<=10;i++){
    for(j=1;j<=10;j++){
        x++;
        sum=sum+x;
    }
  }
  printf("%d",sum);
}
