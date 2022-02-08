#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void swap(int *,int *);

int comp=0;

struct heap{

    int heap_size;

    int *A;


};


void max_heapify(struct heap *max_heap,int i){

    int left=2*i;
    int right=left+1;

    int largest=i;
    
    if(left<=(*max_heap).heap_size){
        comp++;
        if((*max_heap).A[left-1]>(*max_heap).A[largest-1]){
            
            largest=left;
        }
    }
    
    if(right<=(*max_heap).heap_size){
        comp++;
        if((*max_heap).A[right-1]>(*max_heap).A[largest-1]) 
        {
            largest =right;
            
        }   
    }

    if(largest!=i){
        
        swap(&max_heap->A[largest-1],&max_heap->A[i-1]);

        max_heapify(max_heap,largest);


    }

}


void build_max_heap(struct heap *max_heap){

    int start=floor((*max_heap).heap_size/2);

    for(int i=start;i>=1;i--){

            max_heapify(max_heap,i);
            
    }


}


void swap(int *a,int *b){
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}



void heapsort(struct heap *max_heap){


    build_max_heap(max_heap);

    

    
    for(int i=(*max_heap).heap_size;i>=2;i--){

        swap(&max_heap->A[0],&max_heap->A[i-1]);

        (*max_heap).heap_size--;
        max_heapify(max_heap,1);
        
    }
    

}


int main(){

    struct heap max_heap;

    int n;
    scanf("%d",&n);

    max_heap.A= (int *)malloc(n*sizeof(int));

    for(int i=0;i<n;i++) scanf("%d",&max_heap.A[i]);

    max_heap.heap_size=n;
    heapsort(&max_heap);

    for(int i=0;i<n;i++){
        printf("%d ",max_heap.A[i]);
    }
    printf("\n%d",comp);
    return 0;
}