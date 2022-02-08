#include<stdio.h>
#include<stdlib.h>

struct Tree{
	int key;
	struct Tree *left,*right,*parent;

};

// typedef and create a type *linked_list

typedef struct Tree *T_node;

struct binary_tree{
	T_node root;
};

// function to create node for tree
T_node create_tree_node(int k){
	T_node temp;

	temp=(T_node)malloc(sizeof(struct Tree));

	if(temp==NULL){
		printf("ERROR creating a new node\n");
		exit(0);
	}
	temp->key=k;
	temp->left=NULL;
	temp->right=NULL;
	temp->parent=NULL;
	return temp;
}   


// data structure queue implementation

// node structure
struct linked_list{
	T_node data;
	struct linked_list *next;
};

// queue structure
struct QUEUE{

	struct linked_list *head;
	struct linked_list *tail;

};

// typedef and create a type *linked_list
typedef struct linked_list *node;

// function to create a new node
node create_node(T_node k){
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

int QUEUEEMPTY(struct QUEUE *Q){

	if(Q->head==NULL){
		return 1;
	}

	return 0;

}

void ENQUEUE(struct QUEUE *Q, node x){

	if(Q->tail == NULL){
		Q->head=Q->tail=x;
		return;
	}

	Q->tail->next = x;
	Q->tail = x;

}

T_node DEQUEUE(struct QUEUE *Q){

	if(QUEUEEMPTY(Q)){

		return NULL;
	}

	T_node val=Q->head->data;
		
	Q->head=Q->head->next;

	if(Q->head==NULL){
		Q->tail = NULL;
	}

	return val;

}



void INSERT(struct binary_tree *T, T_node z){
	// insert using level order	
	T_node root=T->root;

	if(root==NULL){
		T->root=z;
		return;
	}
	// do level order
	T_node x;
	struct QUEUE queue;
	node queue_node;
	queue.head=NULL;
	queue.tail=NULL;

	queue_node=create_node(root);
	ENQUEUE(&queue,queue_node);

	while(!QUEUEEMPTY(&queue)){
		x=DEQUEUE(&queue);

		if(x->left==NULL){
			x->left=z;
			return;
		}
		else{
			queue_node=create_node(x->left);
			ENQUEUE(&queue,queue_node);
		}

		if(x->right==NULL){
			x->right=z;
			return;
		}
		else{
			queue_node=create_node(x->right);
			ENQUEUE(&queue,queue_node);
		}

	}


}

int close_bracket_count=0;

void PRINT(T_node root){

	if(root==NULL){
		printf("( ) ");
	}
	else{
		printf("( ");
	}

	if(root != NULL){
		printf("%d ",root->key);
		PRINT(root->left);
		PRINT(root->right);
		printf(") ");

	}
}


int main(){
	char ch;
	struct binary_tree T;
	T.root= NULL;
	int val;

	T_node new_node;

	do{
			scanf("%c",&ch);

			switch(ch){

				case 'i':
					scanf("%d",&val);
					new_node=create_tree_node(val);
					INSERT(&T,new_node);
					break;

				case 'p':
					PRINT(T.root);
					printf("\n");
					break;

			}

	}while(ch!='e');


	return 0; 
}