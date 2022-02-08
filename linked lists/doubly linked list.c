#include<stdio.h>
#include<stdlib.h>

// node structure
struct linked_list{
    int val;
    struct linked_list *next;
    struct linked_list *prev;
};

struct List{
    struct linked_list *head;
};

// typedef the struct node to node 
typedef struct linked_list *node;

// function to create a new node
node create_node(int k){
    node temp;

    temp=(node)malloc(sizeof(struct linked_list));

    if(temp==NULL){
        printf("ERROR creating a new node\n");
        exit(0);
    }
    temp->val=k;
    temp->next=NULL;
    temp->prev=NULL;
    return temp;
}   


void list_insert_front(struct List *L,node new_node){

    if(L->head == NULL){ // if list is empty
        (L->head)=new_node;
        return;
    }

    // the next node after the inserted node is the previous head
    new_node->next = (L->head);
    (L->head)->prev= new_node;// previous pointer of old head 
    (L->head)=new_node;

}

void list_insert_tail(struct List *L,node new_node){


    node current_node=(L->head);

    if(current_node==NULL){
        (L->head)=new_node;
        return;
    }
    //creating a dummy node for storing previously visited nodes
    while(current_node->next != NULL){
        current_node=current_node->next;
    }

    current_node->next = new_node;
    new_node->prev=current_node;
    new_node->next = NULL; // already a null

}


node list_search(struct List *L,int k){

    node temp=(L->head);

    if(temp==NULL){// if the list is empty
        return NULL;
    }

    while(temp!=NULL){
        if(temp->val==k){
            return temp;
        }
        temp=temp->next;
    }
    return NULL;

}

void list_insert_after(struct List *L,node new_node,node node_y){

    if(node_y==NULL){
        return;
    }

    // if the node y is the last nodes
    if(node_y->next== NULL){

        new_node->next = NULL;
        new_node->prev = node_y;

        node_y->next=new_node;
        return;
    }

    //connecting newnode to next element of node y
    new_node->next = node_y->next;
    (node_y->next)->prev = new_node;
    //connecting newnode to previous element of node y
    node_y->next = new_node;
    new_node->prev = node_y;


}

void list_insert_before(struct List *L,node new_node,node node_y){

    if(node_y==NULL){
        return;
    }


    if(node_y->prev== NULL){// nody is head

        node_y->prev=new_node;
        new_node->next=node_y;
        (L->head)=(L->head)->prev;
        return;
    }

    node prev_node=node_y->prev;

    prev_node->next=new_node;
    new_node->prev=prev_node;

    new_node->next=node_y;
    node_y->prev=new_node;

}

void list_delete(struct List *L,node node_y){


    if((L->head)==NULL){
        printf("%d\n",-1);
        return;
    }

    if(node_y==NULL){// print -1 if the node does not exist
        printf("%d\n",-1);
        return;
    }

    // print the key of the deleting node
    printf("%d\n",node_y->val);

    
    // if the list is a single element list ie => only head case

    if(node_y==(L->head) && node_y->next==NULL){
        (L->head)=NULL;
        free(node_y);
        return;
    }

    if(node_y==(L->head)){// head case /
            // or node_y->prev==null case

        (node_y->next)->prev = NULL;

        (L->head)=node_y->next;

        free(node_y);
        return;
    }

    if(node_y->next==NULL){// tail case

        (node_y->prev)->next=NULL;

        free(node_y);
        return;
    }

    // middle case
    node prev_node = node_y->prev;
    node next_node = node_y->next;

    prev_node->next = next_node;
    next_node->prev = prev_node;

    free(node_y);


}

void list_delete_initial(struct List *L){

    node node_y=L->head;

    if((L->head)==NULL) {

        printf("%d\n",-1);
        return;

    }

    printf("%d\n",node_y->val);
    // if the list is a single element list ie => only head case
    if(node_y==(L->head) && node_y->next==NULL){
        (L->head)=NULL;
        free(node_y);
        return;
    }

    (node_y->next)->prev = NULL;

    (L->head)=node_y->next;

    free(node_y);

}

void list_delete_last(struct List *L){

    node last_node=L->head;

    // return if the list is empty
    if(last_node==NULL){
        printf("%d\n",-1);
        return;
    }

    while(last_node->next!=NULL){ 

        last_node=last_node->next;
    }

    //print key of the last node
    printf("%d\n",last_node->val);


    node prev_node=last_node->prev;
    // the case when the prev node is the head => a single element list
    if(prev_node==NULL){
        L->head=NULL;
        free(last_node);
        return;
    }
    prev_node->next=NULL;
    free(last_node);
}

void print_llist(struct List *L){
    node temp=(L->head);
    while(temp != NULL){ // boundary when temp is null(end)
        printf("%d\n",temp->val);
        temp=temp->next;    
    }
}


int main(){

    //the list structure
    struct List L;
    L.head=NULL;

    char ch;// choice for menu
    int val,y; // insert value 
    // input nodes
    node new_node,node_y;

    do{
        scanf("%c",&ch);

        switch(ch){

            case 'f':
                scanf("%d",&val);
                new_node=create_node(val); // create a new node
                
                list_insert_front(&L,new_node);
                
                break;


            case 't':
                scanf("%d",&val);
                new_node= create_node(val);

                list_insert_tail(&L,new_node);
                break;

            case 'a':
                scanf("%d %d",&val,&y);// y-> reference node
                
                // creating the new node
                new_node=create_node(val);

                node_y=list_search(&L,y);

                list_insert_after(&L,new_node,node_y);
                break;

            case 'b':
                scanf("%d %d",&val,&y);

                new_node=create_node(val);

                node_y=list_search(&L,y);

                list_insert_before(&L,new_node,node_y);
                break;

            case 'd':
                scanf("%d",&val);

                node_y=list_search(&L,val);

                list_delete(&L,node_y);
                break;

            case 'i':
                list_delete_initial(&L);
                break;

            case 'l':
                list_delete_last(&L);
                break;

            case 's':
                scanf("%d",&val);
                if(list_search(&L,val)!=NULL){
                    printf("%d\n",1);
                }
                else{
                    printf("%d\n",-1);
                }
                break;
        }


    }while(ch!='e'); // exit when 'e'


    return 0;
}