#include <stdio.h>

int tail_sum(int tab[],int size,int suma){
    if(size==0)return suma;
    return tail_sum(tab,size-1,tab[size-1]+suma);
}

#define SIZE 1000000
int tab[SIZE];
int main() {
    for(int i=0;i<SIZE;i++)tab[i]=i%10;
    printf("tail sum = %d\n",tail_sum(tab,sizeof(tab)/sizeof(tab[0]),0));
    return 0;
}
