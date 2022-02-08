
#include<stdio.h>

long binary_search(int arr[],long l,long r,int val){

	if(l>r){
		return -1;
	}

	long mid=l+(r-l)/2;

	if(arr[mid]==val){
		return mid;
	}

	if(arr[mid]<val){
		l=mid+1;
	}

	if(val<arr[mid]){
		r=mid-1;
	}

	return binary_search(arr,l,r,val);

}



int main(){

	long n,index=-1,m=0;
	int val;
	// read the size of array

	scanf("%ld",&n);

	// read the number of queries

	scanf("%ld",&m);

	int arr[n];
	
	// read the array values
	
	for(long i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}

	// read the queries 

	for(long i=0 ; i<m ; i++)
	{
		// read the value to search
	
		scanf("%d",&val);
		
		// binary search function
		
		index=binary_search(arr,0,n-1,val);

		long first=index;
		
		// if the element is found
		
		if(index!=-1){
			// try to find the first occurence of the element
			for( first = index ; first>=0 ; first-- ){
				if(arr[first]!=val){
					first++;
					break;
				}
			}
			// if the first occurence of the search value is the first value of the array
			if(first==-1) first++;
			
			printf("%ld\n",first);
		}
		else{
			printf("%ld\n",index);
			
		}
	}

	return 0;

}
