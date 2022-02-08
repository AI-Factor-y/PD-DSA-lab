#include<stdio.h>

// global variable for counting the number of 
// comparisons
int comp=0;


void merge(int A[],int p,int q,int r){

	int n1=q-p+1;
	int n2=r-q;
	int L[n1+1],R[n2+1];

	for(int i=0;i<n1;i++){
		L[i]=A[p+i];
	}
	for(int i=0;i<n2;i++){
		R[i]=A[q+i+1];
	}

	// seting sentinal values to the 
	// end of left and right array
	L[n1]=99999;
	R[n2]=99999;

	int left_ptr=0,right_ptr=0;

	for(int k=p;k<=r;k++){
		comp++;
		if(L[left_ptr]<=R[right_ptr]){
			A[k]=L[left_ptr];
			left_ptr++;
		}
		else{
			A[k]=R[right_ptr];
			right_ptr++;
		}
	}


}

// merge sort function to sort the array

void merge_sort(int A[], int p, int r){

	if(p<r){

		int mid=(p+(r-p)/2);  // p+(r-p)/2

		merge_sort(A,p,mid);

		merge_sort(A,mid+1,r);

		merge(A,p,mid,r);

	}

}

// print function to print the array

void print(int arr[],int n){
	for(int i=0;i<n;i++){
		printf("%d ",arr[i]);
	}
}


int main(){

	int n;
	// read the size
	scanf("%d",&n);

	int arr[n];

	// read the array elements

	for(int i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}

	comp=0;
	// applying merge sort on the array

	merge_sort(arr,0,n-1);

	// print the array
	print(arr,n);

	// print the number of comparisons

	printf("\n%d",comp);


	return 0;
}		