#include<stdio.h>
#include<stdlib.h>

// node structure
struct linked_list{
    int val;
    struct linked_list *next;
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
    return temp;
}   


void list_insert_front(struct List *L,node new_node){
    
    // the next node after the inserted node is the previous head
    new_node->next = (L->head);
 
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

    new_node->next=node_y->next;

    node_y->next=new_node;

}

void list_insert_before(struct List *L,node new_node,node node_y){


    node search_node;
    node prev_node=NULL;
        
    // if the node to be searched is invalid
    if(node_y==NULL){
        return;
    }

    search_node=(L->head);
    while(search_node!=NULL){

        if(search_node->val==node_y->val){
            break;
        }
        prev_node=search_node;
        search_node=search_node->next;
    }

    if(prev_node==NULL) // if the search node is the head
    {   //insert at front
        list_insert_front(L,new_node);
        return;
    }

    prev_node->next=new_node;
    new_node->next=search_node;


}

void list_delete(struct List *L,node node_x){


    node search_node=(L->head),prev_node;

    prev_node=NULL;

    if(node_x==NULL){

        printf("%d\n",-1);

        return;
    }

    if((L->head)==NULL){
        printf("%d\n",-1);
        return;
    }

    while(search_node!=NULL){
        if(search_node->val==node_x->val){
            break;
        }
        prev_node=search_node;
        search_node=search_node->next;
    }   

    if(search_node==NULL){// print -1 if the node does not exist
        printf("%d\n",-1);
        return;
    }

    // print the key of the deleting node
    printf("%d\n",search_node->val);

    if(search_node==(L->head)){
        (L->head)=search_node->next;
        free(search_node);
        return;
    }

    prev_node->next=search_node->next;

    free(search_node);


}

void list_delete_first(struct List *L){

    node first_node=L->head;

    if(first_node==NULL) {

        printf("%d\n",-1);
        return;

    }

    L->head=first_node->next;

    // print deleted key

    printf("%d\n",first_node->val);

    free(first_node);

}

void list_delete_last(struct List *L){

    node last_node=L->head;
    node prev_node=NULL;

    // return if the list is empty
    if(last_node==NULL){
        printf("%d\n",-1);
        return;
    }

    while(last_node->next!=NULL){ 

        prev_node=last_node; 
        last_node=last_node->next;

    }
    //print key of the last node
    printf("%d\n",last_node->val);

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
                list_delete_first(&L);
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