#include<stdio.h>
#include<stdlib.h>

// node structure
struct linked_list{
	int data;
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

void DEQUEUE(struct QUEUE *Q){

	if(QUEUEEMPTY(Q)){
		printf("%d\n",-1);
		return;
	}

	int val=Q->head->data;
		
	Q->head=Q->head->next;

	if(Q->head==NULL){
		Q->tail = NULL;
	}

	printf("%d\n",val);

}


int main(){

	struct QUEUE Q;

	Q.head=NULL;
	Q.tail=NULL;

	int k;
	char ch;
	int n,val;
	node x;

	do{
		// read choice
		scanf("%c",&ch);

		switch(ch){

			case 'i':
				scanf("%d",&k);
				x=create_node(k);
				ENQUEUE(&Q,x);
				break;

			case 'd':
				DEQUEUE(&Q);
				break;


			case 'e':
				val=QUEUEEMPTY(&Q);
				printf("%d\n",val);
				break;

		}

	}while(ch!='t');


}