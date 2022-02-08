#include<stdio.h>
#include<stdlib.h>

struct linked_list{
	int data;
	struct linked_list *next;
};

struct STACK{

	struct linked_list *top;
};

// typedef and create a type *linked_list
typedef struct linked_list *node;


// function to create a new node
node create_node(int k){
	node temp;

	temp=(node)malloc(sizeof(struct linked_list));

	if(temp==NULL){
		printf("ERROR creating a new node\n");
		exit(0);
	}
	temp->data=k;
	temp->next=NULL;
	return temp;
}   


int STACK_EMPTY(struct STACK *S){

	if((S->top)==NULL){
		return -1;
	}

	return 1;
}


void PUSH(struct STACK *S,node x){
   
	x->next = (S->top);

	(S->top)=x;

}


void POP(struct STACK *S ){


	node first_node=S->top;

	if(first_node==NULL) {

		printf("%d\n",-1);
		return;

	}

	S->top=first_node->next;

	// print deleted key

	printf("%d\n",first_node->data);

	free(first_node);

}



int main(){

	char ch;

	// stack creation
	struct STACK S;
	S.top=NULL;

	int k,n,del;
	int is_empty;// if the stack is empty
	// nodes
	node x;

	do{ // menu
		//read a character
		scanf("%c",&ch);

		switch(ch){

			case 'i':
				scanf("%d",&k); // the val to be inserted
				x=create_node(k);
				PUSH(&S,x);
				break;

			case 'd':
				POP(&S); // pop element
				break;

			case 'e':
				is_empty=STACK_EMPTY(&S);
				printf("%d\n",is_empty);
				break;

		}
	
	}while(ch!='t');



	return 0;
}