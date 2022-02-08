#include<stdio.h>


int insertion_sort(int arr[],int n){

	int key,comp=0;
	int j=0;
	for(int i=1;i<n;i++){

		key=arr[i];
		j=i-1;
		while(j>=0){
			comp++;
			if(arr[j]>key){
				arr[j+1]=arr[j];
				j--;
			}
			else{
				break;
			}
		}

		arr[j+1]=key;

	}
	return comp;

}


void print(int arr[],int n){

	for(int i=0;i<n;i++){
		printf("%d ",arr[i]);
	}
	
}


int main(){

	int n,count_comp=0;

	scanf("%d",&n);

	int arr[n];

	for(int i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}

	count_comp=insertion_sort(arr,n);

	print(arr,n);

	printf("\n%d",count_comp);
	return 0;


}