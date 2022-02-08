#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define inf 99999

struct heap{

    int heap_size;

    int *A;

    int arr_size;
};


void swap(int * ,int *);

void min_heapify(struct heap *,int );

int heap_minimum(struct heap *);

int heap_extract_min(struct heap *);

void min_heap_insert(struct heap *,int );

void heap_decrease_key(struct heap *,int ,int );

int parent(int );

void swap(int *a,int *b){
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}


void min_heapify(struct heap *min_heap,int i){


    int left=i*2;
    int right=left+1;

    int smallest = i;

    if(left<=(*min_heap).heap_size && (*min_heap).A[left-1]<(*min_heap).A[smallest-1]){
        smallest=left;
    }

    if(right<=(*min_heap).heap_size && (*min_heap).A[right-1]<=(*min_heap).A[smallest-1]){
        smallest= right;
    }

    if(smallest!=i){

        swap(&min_heap->A[smallest-1],&min_heap->A[i-1]);

        min_heapify(min_heap,smallest);


    }



}

int heap_minimum(struct heap *min_heap){
    if((*min_heap).heap_size<1){

        return -1;
    }
    return (*min_heap).A[0];
}

int heap_extract_min(struct heap *min_heap){

    if((*min_heap).heap_size<1){
        return -1;
    }

    int min=(*min_heap).A[0];
    
    (*min_heap).A[0]=(*min_heap).A[(*min_heap).heap_size-1];

    (*min_heap).heap_size--;

    min_heapify(min_heap,1);

    return min;


}


void min_heap_insert(struct heap *min_heap,int val){
    (*min_heap).heap_size++;

    // printf("%d - heap_size      %d - arr_size\n",(*min_heap).heap_size,(*min_heap).arr_size);

    if((*min_heap).heap_size>=(*min_heap).arr_size){
        (*min_heap).arr_size*=2;
        // printf("the array size is : %d \n",(*min_heap).arr_size);
        int *ptr=(*min_heap).A;
        (*min_heap).A = (int*)realloc(ptr, (*min_heap).arr_size * sizeof(int));
    }

    (*min_heap).A[((*min_heap).heap_size)-1]=inf;

    heap_decrease_key(min_heap,(*min_heap).heap_size,val);


}

void heap_decrease_key(struct heap *min_heap,int i,int key){

    if(key>(*min_heap).A[i-1]){
        printf("\nnew key is larger than current key");
        return ;
    }

    (*min_heap).A[i-1]=key;

    while( i>1 && (*min_heap).A[parent(i)-1]>(*min_heap).A[i-1]){
        swap(&min_heap->A[i-1],&min_heap->A[parent(i)-1]);
        i=parent(i);
    }
}

int parent(int i){
    return floor(i/2);
}

void print(int arr[], int heap_size){
    for(int i=0;i<heap_size;i++){
                    printf("%d ",arr[i]);
                }
        printf("\n");
}

int main(){

    struct heap min_heap;

    char ch;
    int min,val,index;;

    min_heap.A = (int *)malloc(1*sizeof(int));
    min_heap.heap_size=0;
    min_heap.arr_size=1;
    do{

        scanf("%c",&ch);

        switch(ch){

            case 'i':
                scanf("%d",&val);
                
                min_heap_insert(&min_heap,val);
                
                
                break;

            case 'e':
                
                min=heap_extract_min(&min_heap);
                printf("%d\n",min);
                

                break;

            case 'm':
                min= heap_minimum(&min_heap);
                printf("%d\n",min);
                

                break;

            case 'd':
               
                scanf("%d %d",&index,&val);
                heap_decrease_key(&min_heap,index+1,val);
                

                break;

        }

    }while(ch!='s');


    return 0;

}