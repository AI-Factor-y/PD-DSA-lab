#include<stdio.h>

struct STACK{
	int top;
	int A[100000];
	int size;
};


int STACK_EMPTY(struct STACK *S){

	if((S->top)<=-1){
		return -1;
	}

	return 1;
}

int STACK_FULL(struct STACK *S){

	if((S->top)>=(S->size - 1)){
		return 1;
	}

	return 0;
}

void PUSH(struct STACK *S,int k){
   
	if( !STACK_FULL(S) ){
		 S->top++;
		 S->A[S->top]=k;

	}
}


int POP(struct STACK *S ){

	if(STACK_EMPTY(S)==-1){
		return -1;
	}

	S->top--;

	int popped = S->A[(S->top)+1];

	return popped;

}



int main(){

	char ch;

	// stack creation
	struct STACK S;
	S.top=-1;

	int k,n,del;
	int is_empty;// if the stack is empty
	// read size of stack
	scanf("%d",&n); 

	S.size=n;

	do{ // menu
		//read a character
		scanf("%c",&ch);

		switch(ch){

			case 'i':
				scanf("%d",&k); // the val to be inserted
				PUSH(&S,k);
				break;

			case 'd':
				del=POP(&S); // deleted element
				printf("%d\n",del);
				break;

			case 'e':
				is_empty=STACK_EMPTY(&S);
				printf("%d\n",is_empty);
				break;

		}
	
	}while(ch!='t');



	return 0;
}