#include<stdio.h>
#include<stdlib.h>

#define INF 999999

struct binomial_node{

	int key;
	struct binomial_node *parent,*child,*sibling;
	int degree;
};

typedef struct binomial_node* b_node;

struct binomial_heap{

	b_node head;

};

typedef struct binomial_heap* B_HEAP; 


//----------------queue functions----------------

// node structure
struct linked_list{
	b_node data;
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
node create_node(b_node k){
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

b_node DEQUEUE(struct QUEUE *Q){

	if(QUEUEEMPTY(Q)==-1){
		printf("%d\n",-1);
		return NULL;
	}

	b_node val=Q->head->data;
		
	Q->head=Q->head->next;

	if(Q->head==NULL){
		Q->tail = NULL;
	}

	return val;

}

//----------------- queue functions end --------------

	
struct List{
    struct linked_list *head;
};


void list_insert_front(struct List *L,node new_node){
    
    // the next node after the inserted node is the previous head
    new_node->next = (L->head);
 
    (L->head)=new_node;

}


//-------------------- heap functions ----------------



b_node create_heap_node(int k){

	b_node temp;

	temp=(b_node)malloc(sizeof(struct binomial_node));

	if(temp==NULL){
		printf("ERROR creating a new node\n");
		exit(0);
	}
	temp->key=k;
	temp->child=NULL;
	temp->sibling=NULL;
	temp->parent=NULL;
	temp->degree=0;
	return temp;

}

B_HEAP make_binomial_heap(){

	B_HEAP H;
	H = (B_HEAP)malloc(sizeof(struct binomial_heap));
	H->head=NULL;
	return H;
}

B_HEAP binomial_heap_merge(B_HEAP H1, B_HEAP H2){

	b_node h1_p = H1->head;
	b_node h2_p = H2->head;

	// merge heap
	B_HEAP merge_heap = make_binomial_heap();
	b_node merge_p = merge_heap->head;

	// standard merge 
	while(h1_p!=NULL && h2_p!=NULL){

		if(h1_p->degree < h2_p->degree){
			
	
			if(merge_heap->head==NULL){

				merge_p= h1_p;	
				merge_heap->head= merge_p;

			}
			else{
				merge_p->sibling = h1_p;
				merge_p = merge_p->sibling;

			}
			h1_p= h1_p->sibling;
		}
		else{

			if(merge_heap->head==NULL){
				merge_p= h2_p;
				merge_heap->head= merge_p;
			}
			else{

				merge_p->sibling = h2_p;
				merge_p = merge_p->sibling;
			}

			h2_p= h2_p->sibling;

		}

	}

	// adding residues
	while(h1_p!=NULL){
		if(merge_heap->head==NULL){

			merge_p= h1_p;	
			merge_heap->head= merge_p;

		}
		else{
			merge_p->sibling = h1_p;
			merge_p = merge_p->sibling;

		}
		h1_p= h1_p->sibling;

	}
	while(h2_p!=NULL){
		if(merge_heap->head==NULL){
			merge_p= h2_p;
			merge_heap->head= merge_p;
		}
		else{

			merge_p->sibling = h2_p;
			merge_p = merge_p->sibling;
		}

		h2_p= h2_p->sibling;
	}

	return merge_heap;
}


void binomial_link(b_node y, b_node z){

	y->parent= z;
	y->sibling= z->child;
	z->child=y;
	z->degree = z->degree+1;
}


B_HEAP binomial_heap_union(B_HEAP H1, B_HEAP H2){

	B_HEAP H = binomial_heap_merge(H1,H2);

	if(H->head==NULL){
		return H;
	}

	free(H1); free(H2);

	b_node prev_x=NULL;
	b_node x= H->head;
	b_node next_x= x->sibling;

	while(next_x!=NULL){

		if((x->degree != next_x->degree) ||
		   (next_x->sibling !=NULL && next_x->sibling->degree== x->degree)){

			prev_x=x;
			x= next_x;
		}
		else{

			if( x->key <= next_x->key){
				x->sibling= next_x->sibling;
				binomial_link(next_x,x);
			}
			else{
				if(prev_x==NULL){
					H->head=next_x;

				}
				else{
					prev_x->sibling= next_x;
				}
				binomial_link(x,next_x);
				x= next_x;
			}
		}
		next_x= x->sibling;
	}
	return H;
}

B_HEAP binomial_heap_insert(B_HEAP H, b_node new_node){

	B_HEAP new_H= make_binomial_heap();

	new_H->head= new_node;

	return binomial_heap_union(H,new_H);
}



b_node binomial_heap_minimum(B_HEAP H){

	b_node min_node = NULL;
	b_node root= H->head; 

	int min_val=INF;
	while(root!=NULL){
		if(root->key <min_val){
			min_val= root->key;
			min_node = root;
		}
		root = root->sibling;
	}
	return min_node;
}



void print_b_tree_bfs(b_node root){

	struct QUEUE Q;
	Q.head=NULL;
	Q.tail=NULL;

	node queue_val=create_node(root);
	ENQUEUE(&Q,queue_val);

	while(!QUEUEEMPTY(&Q)){

		b_node cur_node= DEQUEUE(&Q);

		while(cur_node!=NULL){

			printf("%d ",cur_node->key);

			if(cur_node->child!=NULL){
				node queue_val=create_node(cur_node->child);
				ENQUEUE(&Q,queue_val);
			}

			cur_node= cur_node->sibling;
		}

	}

}

void print_heap(B_HEAP H){


	b_node root= H->head;
	
	while(root!=NULL){
			
		printf("%d ",root->key);
		if(root->child!=NULL){
			print_b_tree_bfs(root->child);
		}
		root=root->sibling;
	}

}

b_node get_node_before(B_HEAP H,b_node x){

	b_node temp= H->head;
	b_node prev=NULL;
	while(temp!=NULL){

		if(temp==x){
			break;
		}
		prev= temp;
		temp=temp->sibling;
	}
	return prev;
}

int binomial_heap_extract_min(B_HEAP *H){

	b_node min_node= binomial_heap_minimum(*H);

	int min_node_val= min_node->key;

	B_HEAP H1= make_binomial_heap();


	// add all child of min_node to list
	struct List L;
	L.head=NULL;

	b_node x= min_node->child;

	while(x!=NULL){
		node new_node=create_node(x);
		list_insert_front(&L,new_node);
		x=x->sibling;
	}
		
	// reverse the sibling pointers in list data
 	if(L.head!=NULL) H1->head= L.head->data;

	node prev=NULL;
	node temp=L.head;
	while(1){
		if(prev!=NULL){
			if(temp!=NULL){
				prev->data->sibling=temp->data;
			}
			else{
				prev->data->sibling=NULL;
			}
			prev->data->parent=NULL;
		}
		if(temp==NULL){
			break;
		}
		prev=temp;
		temp=temp->next;
	}
	// delete the min_node
	if((*H)->head==min_node){
		(*H)->head=min_node->sibling;
	}
	else{	
		b_node prev_min=get_node_before((*H),min_node);

		prev_min->sibling=min_node->sibling;
	}
	min_node=NULL;
	free(min_node);
	// unite the two heaps;
	(*H)= binomial_heap_union((*H),H1);
	return min_node_val;

}
	

b_node search_node(b_node root,int k){
	if(root==NULL){
		return NULL;
	}

	if(root->key==k) return root;

	b_node s_child= search_node(root->child,k);
	if(s_child!=NULL) return s_child;

	b_node s_sibl=search_node(root->sibling,k);
	if(s_sibl!=NULL) return s_sibl;

	return NULL;
}

void decrease_key(B_HEAP H, b_node x, int k){

	if(x==NULL){
		printf("-1\n");
		return;
	}

	if(k> x->key){
		printf("-1\n");
		return;
	}

	x->key =k;
	b_node y=x;
	b_node z=y->parent;
	int temp;
	while(z!=NULL && y->key < z->key){
		temp=y->key;
		y->key=z->key;
		z->key=temp;
		y=z;
		z=y->parent;
	}

}

void DELETE(B_HEAP *H,b_node x){

	decrease_key(*H,x, -INF);

	binomial_heap_extract_min(H);
}

int main(){

	B_HEAP H=make_binomial_heap();

	int val,key_val;
	char ch;
	b_node new_node;

	do{
		scanf("%c",&ch);

		switch(ch){

			case 'i':
				scanf("%d",&val);
				new_node= create_heap_node(val);

				H=binomial_heap_insert(H,new_node);
				break;

			case 'p':
				print_heap(H);
				printf("\n");
				break;
			case 'x':

				if(H->head==NULL){
					printf("-1\n");
				}
				else{
					val=binomial_heap_extract_min(&H);
					printf("%d\n",val);
				}
				break;

			case 'm':

				if(H->head==NULL){
					printf("-1\n");
				}
				else{
					new_node=binomial_heap_minimum(H);
					printf("%d\n",new_node->key);
				}
	
				break;

			case 'r':
				scanf("%d %d",&val,&key_val);
				new_node=search_node(H->head,val);
				decrease_key(H,new_node,key_val);
				break;

			case 'd':
				scanf("%d",&val);
				new_node=search_node(H->head,val);
				if(new_node==NULL){
					printf("-1\n");
				}
				else{
					DELETE(&H,new_node);
				}
				
				break;
		}


	}while(ch!='e');

	return 0;
}