#include<stdio.h>


int gcd(int a,int b){

	if(a==0){
		return b;
	}

	return gcd(b%a,a);

}

int main(){

	int a,b;
	int gcd_value;
	
	// read two numbers 
	
	scanf("%d",&a);
	scanf("%d",&b);
	
	// if number is negetive then make it positive
	
	if(a<0){
		a*=-1;
	}
	if(b<0){
		b*=-1;
	}
	
	// if both input is 0 , invalid inputs
	
	if(a==0 && b==0){
		printf("%d",-1);
		return 0;
	}
	
	// gcd function call
	
	gcd_value=gcd(a,b);

	printf("%d",gcd_value);
	return 0;


}
