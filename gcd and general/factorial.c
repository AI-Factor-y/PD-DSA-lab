#include<stdio.h>


long factorial( long n){
	
	
	if(n==0){
		return 1;
	}
	// if number is negetive, invalid input
	if(n<0){
		return -1;
	}
	
	return n*factorial(n-1);
}


int main(){

	long a;
	long fact;
	
	// read the input
	
	scanf("%ld",&a);
	
	// find the factorial of the input
	
	fact=factorial(a);

	printf( "%ld", factorial(a) );

	return 0;

}
