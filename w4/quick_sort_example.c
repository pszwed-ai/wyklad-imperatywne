//
// Created by pszwed on 21.03.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void swap(int*a,int*b){
    int tmp=*a;
    *a=*b;
    *b=tmp;
}

int partition(int tab[],int p, int r) {
    int pivot = tab[r-1];
    int i=p;
    for(int j=p;j<r-1;j++){
        if(tab[j]<pivot){
            swap(tab+i,tab+j);
            i++;
        }
    }
    swap(tab+i,tab+r-1);
    return i;
}

void print(int tab[],int n){
    for(int i=0;i<n;i++)printf("%d ",tab[i]);
    printf("\n");
}

int test_partition(){
    int tab[]={11,2,6,5,8,9,12,3,4,7};
    int n=sizeof(tab)/sizeof(tab[0]);
    print(tab,n);
    int q= partition(tab,0,n);
    print(tab,q);
    printf("q=%d tab[q]=%d\n",q,tab[q]);
    print(tab+q+1,n-q-1);
}

void quick_sort(int tab[],int p, int r){
    if(p>=r-1)return;
    int q = partition(tab,p,r);
    quick_sort(tab,p,q);
    quick_sort(tab,q+1,r);
}

void test_qsort(){
    int tab[]={11,2,6,5,8,9,12,3,4,7};
    int n=sizeof(tab)/sizeof(tab[0]);
    print(tab,n);
    quick_sort(tab,0,n);
    print(tab,n);
}

////////////////////////////////////////////////////////////////////////////////////////////////

#define STACK_SIZE 100
struct {int p; int r;} stack [STACK_SIZE];
int stack_cnt=0;
int stack_max=0;

int stack_is_empty(){
    return stack_cnt==0;
}

int stack_push(int p,int r){
   if(stack_cnt==STACK_SIZE)return 0;
   stack[stack_cnt].p=p;
   stack[stack_cnt].r=r;
   stack_cnt++;
   if(stack_cnt>stack_max){
       stack_max = stack_cnt;
   }
   return 1;
}

int stack_pop(int*p,int*r){
    if(stack_cnt==0)return 0;
    *p = stack[stack_cnt-1].p;
    *r = stack[stack_cnt-1].r;
    stack_cnt--;
    return 1;
}

void stack_dump(){
    for(int i=0;i<stack_cnt;i++){
        printf("[%d %d] ",stack[i].p,stack[i].r);
    }
    printf("\n");
}

void it_quick_sort(int tab[],int p, int r,int trace){
    stack_push(p,r);
    if(trace)stack_dump();
    while(!stack_is_empty()){
        stack_pop(&p,&r);
        int q = partition(tab,p,r);
        if(p<q-1)stack_push(p,q);
        if(q+1<r-1)stack_push(q+1,r);
        if(trace)stack_dump();
    }
}

void test_it_qsort(){
    int tab[]={11,2,6,5,8,9,12,3,4,7};
    int n=sizeof(tab)/sizeof(tab[0]);
    print(tab,n);
    it_quick_sort(tab,0,n,1);
    print(tab,n);
}

int is_sorted(int tab[],int n){
    for(int i=0;i<n-1;i++){
        if(tab[i]>tab[i+1])return 0;
    }
    return 1;
}

void set_random(int*tab,int n){
    for(int i=0;i<n;i++)tab[i]=random()%n;
}

void test_big_qsort(){
    int n = 1000000;
    int*tab = malloc(n*sizeof(int));
    // Zakomentuj set_random() i zobacz co się stanie?
    // Dlaczego?
    set_random(tab,n);
    clock_t start = clock();
    quick_sort(tab,0,n);
    clock_t end = clock();
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("sorted:%d time:%f sec\n",is_sorted(tab,n),seconds);
    free(tab);
}

void test_big_it_qsort(){
    int n = 1000000;
    int*tab = malloc(n*sizeof(int));
    // Zmniajsz n na 100_000, zakomentuj set_random() i zobacz co się stanie?
    // Dlaczego?
    set_random(tab,n);
    clock_t start = clock();
    it_quick_sort(tab,0,n,0);
    clock_t end = clock();
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("sorted:%d time:%f sec stack_max=%d\n",is_sorted(tab,n),seconds,stack_max);
    free(tab);
}

void get_stack_time(int n,int*stack_used,float*time){
    stack_max=0;
    int*tab = malloc(n*sizeof(int));
    set_random(tab,n);
    clock_t start = clock();
    it_quick_sort(tab,0,n,0);
    clock_t end = clock();
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    free(tab);
    *stack_used = stack_max;
    *time=seconds;
}

void it_qsort_performance(){
    int n=100;
    for(int i=0;i<12;i++){
        int stack_used;float time;
        get_stack_time(n,&stack_used,&time);
        double nln = n*log(n);
        double ln=log(n);
        printf("%d: n = %09d \ttime = %f \tmax_stack=%2d\t [t/nln=%e stack/ln=%f]\n",
                i,n,time,stack_used,time/nln,stack_used/ln);
        n*=5;
    }
}

int main(){
//    test_partition();
//    test_qsort();
//    test_it_qsort();
    test_big_qsort();
    test_big_it_qsort();
//    it_qsort_performance();
}