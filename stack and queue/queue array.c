#include<stdio.h>


struct QUEUE{

	int head;
	int tail;
	int A[100000];
	int size;
};


int QUEUEFULL(struct QUEUE *Q){

	int val= (Q->tail + 1)%(Q->size);
	if(val == (Q->head)){
		return -1;
	}
	return 1;
}

int QUEUEEMPTY(struct QUEUE *Q){

	if((Q->head)==-1 && (Q->tail)==-1){
		return -1;
	}

	return 1;

}

void ENQUEUE(struct QUEUE *Q, int k){

	if(QUEUEFULL(Q)==-1){
		return;
	}

	if(Q->head==-1 || Q->tail==-1){
		Q->head=0;
		Q->tail=0;
	}
	else{
		Q->tail= (Q->tail + 1)%(Q->size);
	}

	Q->A[Q->tail]=k;

	
}

void DEQUEUE(struct QUEUE *Q){

	if(QUEUEEMPTY(Q)==-1){
		printf("%d\n",-1);
		return;
	}

	int val=Q->A[Q->head];

	if(Q->head == Q->tail){
		Q->head=-1;
		Q->tail=-1;
	}
	else{
		Q->head= (Q->head+1)%(Q->size);
	}

	printf("%d\n",val);

}


int main(){

	struct QUEUE Q;

	Q.head=-1;
	Q.tail=-1;

	int k;
	char ch;
	int n,val;

	// size of the array;
	scanf("%d",&n);

	Q.size=n;

	do{
		// read choice
		scanf("%c",&ch);

		switch(ch){

			case 'i':
				scanf("%d",&k);
				ENQUEUE(&Q,k);
				break;

			case 'd':
				DEQUEUE(&Q);
				break;

			case 'f':
				val=QUEUEFULL(&Q);
				printf("%d\n",val);
				break;

			case 'e':
				val=QUEUEEMPTY(&Q);
				printf("%d\n",val);
				break;

		}

	}while(ch!='t');


}