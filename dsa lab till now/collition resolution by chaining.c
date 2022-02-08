#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// node structure
struct linked_list{
	char *word;
	struct linked_list *next;
};

struct List{
	struct linked_list *head;
};

struct HTable{

	struct List *table;
	int size;

};


// typedef the struct node to node 
typedef struct linked_list *node;

// function to create a new node
node create_node(char *word){
	node temp;

	temp=(node)malloc(sizeof(struct linked_list));

	if(temp==NULL){
		printf("ERROR creating a new node\n");
		exit(0);
	}
	temp->word=word;
	temp->next=NULL;
	return temp;
}   


void list_insert_tail(struct List *L,node new_node){


	node current_node=(L->head);

	if(current_node==NULL){
		(L->head)=new_node;
		return;
	}
	//creating a dummy node for storing previously visited nodes
	while(current_node->next != NULL){
		// avoiding multiple occurence of a word
		if(strcmp(current_node->word,new_node->word)==0){
			return;
		}
		current_node=current_node->next;
	}

	current_node->next = new_node;
	new_node->next = NULL; // already a null

  

}

node list_search(struct List *L,char *word){

	node temp=(L->head);

	if(temp==NULL){// if the list is empty
		return NULL;
	}

	while(temp!=NULL){
		if(strcmp(temp->word,word)==0){// search for the word
			return temp;
		}
		temp=temp->next;
	}
	return NULL;

}


struct HTable CREATE_TABLE(int k){
	struct HTable HT;
	HT.size=k;
	HT.table=(struct List *)malloc(k*sizeof(struct List));

	for(int i=0;i<k;i++){
		HT.table[i].head=NULL;
	}

	return HT;
}

int split_into_words(char *line, char words[1000][1000]){

	int i=0,j=0,k=0;

	while(1){

		if(line[i]==' '){
			words[k][j++]='\0';
			k++;
			j=0;
		}
		else{
			words[k][j++]=line[i];
		}

		if(line[i]=='\0') break;

		i++;
	}

	return k;

}

void INSERT_TO_TABLE(struct HTable *HT,char word[1000]){

	int size=strlen(word);
	int hash_value=(size*size)%(HT->size);

	node new_node=create_node(word);

	node search_node = list_search(&(HT->table[hash_value]),word);
	if(search_node==NULL){

	list_insert_tail(&(HT->table[hash_value]),new_node);

	}

}

void Insert_elements(struct HTable *HT,char *line){

	int k=0;

	char words[1000][1000];

	int n=split_into_words(line,words);

	for(int i=0; i<=n;i++){

		INSERT_TO_TABLE(HT,words[i]);
		
	}


}


void PRINT_TABLE(struct HTable *HT){

	for(int i=0; i<HT->size; i++){

		node root=HT->table[i].head;
		printf("%d:",i);

		int is_start=1;
		int is_empty=1;

		while(root!=NULL){
			if(is_start){
				printf("%s",root->word);
			}
			else{
				printf("-%s",root->word);
			}
			is_start=0;
			is_empty=0;
			root=root->next;
		}

		if(is_empty){
			printf("null");
		}
		printf("\n");
	}

}

int main(){

	int k;
	struct HTable HT;
	char line[100000];

	scanf("%d",&k);

	scanf("\n%[^\n]",line);


	HT=CREATE_TABLE(k);

	Insert_elements(&HT,line);

	PRINT_TABLE(&HT);

	return 0;
}