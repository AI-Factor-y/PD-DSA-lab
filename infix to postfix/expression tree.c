#include<stdio.h>
#include<stdlib.h>

struct Tree{
	char data;
	struct Tree *left,*right;

};

struct linked_list{
	struct Tree *T_data;

	struct linked_list *next;
};

struct STACK{

	struct linked_list *top;
};

// typedef and create a type *linked_list
typedef struct linked_list *node;
typedef struct Tree *T_node;

struct exp_Tree{

	T_node root;

};

// function to create node for tree
T_node create_tree_node(char k){
	T_node temp;

	temp=(T_node)malloc(sizeof(struct Tree));

	if(temp==NULL){
		printf("ERROR creating a new node\n");
		exit(0);
	}
	temp->data=k;
	temp->left=NULL;
	temp->right=NULL;
	return temp;
}   


// function to create a new node for stack
node create_node(T_node k){
	node temp;

	temp=(node)malloc(sizeof(struct linked_list));

	if(temp==NULL){
		printf("ERROR creating a new node\n");
		exit(0);
	}
	temp->T_data=k;
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


T_node POP(struct STACK *S ){


	node first_node=S->top;

	if(first_node==NULL) {

		return NULL;

	}

	S->top=first_node->next;

	// print deleted key
	T_node popped_node = first_node->T_data;

	free(first_node);

	return popped_node;

}

int is_oparand(char c){

	return (c>='a' && c <= 'z') || (c>='A' && c <='Z');

}


T_node Construct_Tree(char postfix_exp[]){

	struct STACK S;
	S.top=NULL;
	T_node temp,popped1,popped2;
	node stack_node;
	for(int i=0; postfix_exp[i]!='\0'; i++){

		if(is_oparand(postfix_exp[i])){

			temp=create_tree_node(postfix_exp[i]);
			stack_node=create_node(temp);
			
			PUSH(&S,stack_node);

		}
		else{

			temp=create_tree_node(postfix_exp[i]);
			
			popped1 = POP(&S);
			popped2 = POP(&S);

			temp->left = popped2;
			temp->right = popped1;

			stack_node =create_node(temp);

			PUSH(&S,stack_node);

		}

	}

	temp=POP(&S);

	return temp;

}

void Inorder(T_node root){

	if(root!=NULL){

		Inorder(root->left);
		printf("%c",root->data);
		Inorder(root->right);

	}

}

void Preorder(T_node root){

	if(root!=NULL){

		printf("%c",root->data);
		Preorder(root->left);
		Preorder(root->right);

	}

}

void Postorder(T_node root){

	if(root!=NULL){

		Postorder(root->left);

		Postorder(root->right);

		printf("%c",root->data );


	}

}

int main(){

	char ch;
	char postfix_exp[10000];

	struct exp_Tree T;

	T.root = NULL;

	do{
		scanf("%c",&ch);

		switch(ch){


			case 'e':
				scanf("%s",postfix_exp);

				(T.root)=Construct_Tree(postfix_exp);

				break;

			case 'i':
				Inorder(T.root);
				printf("\n");
				break;

			case 'p':
				Preorder(T.root);
				printf("\n");
				break;

			case 's':
				Postorder(T.root);
				printf("\n");
				break;


		}


	}while(ch!='t');

	return 0;
}