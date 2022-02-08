#include<stdio.h>
#include<stdlib.h>


// global variable for the number of comparisons
int comp=0;

void swap(int *a,int *b){
	int temp=*a;
	*a=*b;
	*b=temp;
}

int PARTITION(int A[],int p,int q,int r){

	swap(&A[q],&A[r]);
	int pivot_elem=A[r];
	int j=p-1;
	for(int i=p;i<r;i++){
		comp++;
		if(A[i]<= pivot_elem){
			j++;
			swap(&A[i],&A[j]);
		}
	}
	swap(&A[j+1],&A[r]);
	
	return j+1;
	
}

void QUICK_SORT(int A[],int p, int r){

	if(p<r){

		int q=r;

		q=PARTITION(A,p,q,r);

		QUICK_SORT(A,p,q-1);

		
		QUICK_SORT(A,q+1,r);

	}

}

void PRINT(int A[], int n){

	for(int i=0;i<n;i++){
		printf("%d ",A[i]);
	}

}


int main(){

	int n;
	scanf("%d",&n);

	int arr[n];

	for(int i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}

	QUICK_SORT(arr,0,n-1);
	
	PRINT(arr,n);
	printf("\n%d",comp);

	return 0;


}
