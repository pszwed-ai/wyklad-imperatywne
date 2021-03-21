//
// Created by pszwed 
//
// gcc -S -O2 tail_recursion.c

#include <stdio.h>

int sum(int tab[],int size) {
    if(size==0)return 0;
    return tab[0]+sum(tab+1,size-1);
}

int tail_sum(int tab[],int size,int suma){
    if(size==0)return suma;
    return tail_sum(tab+1,size-1,tab[0]+suma);
}

int main() {
    int tab[]={4,3,2,1};
    printf("sum = %d\n",sum(tab,4));
    printf("tail sum = %d\n",tail_sum(tab,4,0));

    return 0;
}
        