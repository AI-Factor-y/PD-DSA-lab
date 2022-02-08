#include<stdio.h>
#include<stdlib.h>


struct linked_list{
	char data;
	struct linked_list *next;
};

struct STACK{

	struct linked_list *top;
};

// typedef and create a type *linked_list
typedef struct linked_list *node;


// function to create a new node
node create_node(char k){
	node temp;

	temp=(node)malloc(sizeof(struct linked_list));

	if(temp==NULL){
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

char TOP_val(struct STACK *S){
	if(S->top==NULL){
		return '1';
	}
	return S->top->data;
}

char POP(struct STACK *S ){


	node first_node=S->top;

	if(first_node==NULL) {

		return '1';

	}

	S->top=first_node->next;

	char popped= first_node->data;

	free(first_node);
	return popped;

}

int is_oparand(char c){

	return (c>='a' && c <= 'z') || (c>='A' && c <='Z');

}

int precidence(char c){
	if(c=='+' || c=='-'){
		return 1;
	}
	else if(c=='*' || c=='/'){
		return 2;
	}

	return -1;
}


char* InfixToPostfix(char* infix_exp){

	static char postfix_exp[100000];

	int k=0;

	struct STACK S;
	S.top=NULL;

	for(int i=0 ; infix_exp[i]!='\0' ; i++){


		if(is_oparand(infix_exp[i])){

			postfix_exp[k++]=infix_exp[i];
		}
		else if (infix_exp[i]=='('){

			node new_node=create_node(infix_exp[i]);

			PUSH( &S , new_node);

		}
		else if(infix_exp[i]==')'){

			while( STACK_EMPTY(&S)==1 && TOP_val(&S)!='('){

				postfix_exp[k++]=POP(&S);
			}
			
			if( STACK_EMPTY(&S)==1 && TOP_val(&S)!='('){
				// no opening bracket
				return postfix_exp; // invalid exp eg: a+b/c)
			}
			else{
				POP(&S); // pop '('
			}

		}
		else{

			while(STACK_EMPTY(&S)==1){
				char top_elem=TOP_val(&S);
				if(precidence(infix_exp[i])<=precidence(top_elem)){
					postfix_exp[k++]=POP(&S);
				}
				else{
					break;
				}
			}
			node push_node=create_node(infix_exp[i]);
			PUSH(&S,push_node);

		}

	}

	while(STACK_EMPTY(&S)==1){
		postfix_exp[k++]=POP(&S);
	}
	postfix_exp[k++]='\0';

	return postfix_exp;
}

int main(){

	char infix_exp[10000],*postfix_result;

	scanf("%s",infix_exp);

	postfix_result=InfixToPostfix(infix_exp);

	printf("%s\n",postfix_result);
	
}