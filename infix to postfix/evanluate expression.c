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

int TOP_val(struct STACK *S){
	if(S->top==NULL){
		return -1;
	}
	return S->top->data;
}

int POP(struct STACK *S ){


	node first_node=S->top;

	if(first_node==NULL) {

		return -1;

	}

	S->top=first_node->next;

	int popped= first_node->data;

	free(first_node);
	return popped;

}

int is_digit(char c){
	return c>='0' && c<='9';
}



int EvaluatePostfix(char* postfix_exp){

	int result=0;

	// stack creation
	struct STACK S;
	S.top=NULL;	
	node new_node;
	int num=0;
	int is_digit_occur=0;
	for(int i=0; postfix_exp[i]!='\0' ;i++){
		
		if(postfix_exp[i]==' '){
			if(is_digit_occur){
				new_node=create_node(num);
				PUSH(&S,new_node);
			}
			num=0;
			is_digit_occur=0;
			continue;
		}
		if(is_digit(postfix_exp[i])){
			
			num=num*10+(postfix_exp[i]-'0');
			is_digit_occur=1;
		}
		else{

			int val1=POP(&S);
			int val2=POP(&S);

			if(postfix_exp[i]=='+'){
				new_node=create_node(val1+val2);
				PUSH(&S,new_node);
			}
			else if(postfix_exp[i]=='-'){
				new_node=create_node(val2-val1);
				PUSH(&S,new_node);
			}
			else if(postfix_exp[i]=='*'){
				new_node=create_node(val1*val2);
				PUSH(&S, new_node);
			}
			else if(postfix_exp[i]=='/'){
				new_node=create_node(val2/val1);
				PUSH(&S,new_node);
			}


		}

	}

	result= POP(&S);
	return result;

}

int main(){

	char postfix_express[10000];
	int postfix_result;

	scanf("%[^\n]%*c",postfix_express);


	postfix_result=EvaluatePostfix(postfix_express);

	printf("%d\n",postfix_result);
	
}