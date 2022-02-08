#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
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

void list_insert_front(struct List *L,node new_node){
    
    // the next node after the inserted node is the previous head
    new_node->next = (L->head);
 
    (L->head)=new_node;

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

int find_power(char word[10000]){

	int index_arr[27];
	for(int i=0;i<27;i++){
		index_arr[i]=0;
	}

	for(int i=0; word[i]!='\0';i++){
		index_arr[word[i]-'a']=1;
	}
	int power_val=0;
	for(int i=0;i<27;i++){
		if(index_arr[i]==1){
			power_val+= pow(2,i);
		}
	}
	return power_val;
}

void INSERT_TO_TABLE(struct HTable *HT,char word[10000]){

	int size=strlen(word);

	int sp_power_val=find_power(word);

	int hash_value=(sp_power_val)%(HT->size);

	node new_node=create_node(word);

	list_insert_front(&(HT->table[hash_value]),new_node);

}

void Insert_elements(struct HTable *HT,char words[200][10000],int n){

	for(int i=0;i<n;i++){

		INSERT_TO_TABLE(HT,words[i]);

	}

}


void print_lexicographic(node root){

	int is_not_empty=0;

	char* words[10000],temp[10000];
	int k=0;

	while(root!=NULL){

		words[k++]=root->word;

		is_not_empty=1;
		root=root->next;
	}

	for(int i=0;i<k;i++){
		for(int j=i+1;j<k;j++){
			if(strcmp(words[i],words[j])>0){
				strcpy(temp,words[i]);
				strcpy(words[i],words[j]);
				strcpy(words[j],temp);
			}
		}
	}
	
	for(int i=0;i<k;i++){
		printf("%s ",words[i]);
	}	

	if(is_not_empty){
		printf("\n");
	}

}


void PRINT_TABLE(struct HTable *HT){

	for(int i=0; i<HT->size; i++){

		node root=HT->table[i].head;
		

		print_lexicographic(root);

	}

}

int main(){

	int k;
	struct HTable HT;
	char line[200][10000];

	scanf("%d",&k);

	for(int i=0;i<k;i++){

		scanf("%s",line[i]);

	}
		
	HT=CREATE_TABLE(255);

	Insert_elements(&HT,line,k);

	PRINT_TABLE(&HT);

	return 0;
}