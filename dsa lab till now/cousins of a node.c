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



int is_cousin_found=0;


int convert_to_number(char *str,int pos){
	int num=0;
	int neg=1;
	if(str[pos]=='-'){
		neg=-1;
		pos++;
	}	
	int i=pos;
	while(str[i]!=' '){
		num=num*10+(str[i]-'0');
		i++;
	}
	num*=neg;
	return num;
}

int get_right(char *str,int pos){
	int brack=1; 

	for(int i=pos+1;str[i]!='\0';i++){
		if(str[i]=='('){
			brack++;
		}
		else if(str[i]==')'){
			brack--;
		}
		if(brack==0){

			return i;
		}
	}
	return -1;

}

void CONVERT_TO_TREE(T_node *root,char *str,int start)
{	

	int i=start;
	if(str[i+2]==')'){
		*root=NULL;
		return;
	}
	else{
		int number=convert_to_number(str,i+2);
		// printf("%d\n",number);
		T_node new_node=create_tree_node(number);
		(*root)=new_node;	
		
	}
	int lbracket_pos=i+2;
	while(str[lbracket_pos]!='(') lbracket_pos++;

	int pos=get_right(str,lbracket_pos);
	// printf("\n pos : %d\n",pos);
	CONVERT_TO_TREE(&((*root)->left),str,lbracket_pos);
	CONVERT_TO_TREE(&((*root)->right),str,pos+2);
	
}

int FIND_LEVEL(T_node root,int val,int level){

	if(root!=NULL){
		if(root->key==val){
			return level;
		}
		int level_val;
		level_val=FIND_LEVEL(root->left,val,level+1);

		if(level_val){
			return level_val;
		}

		level_val=FIND_LEVEL(root->right,val,level+1);

		return level_val;

	}
	return 0;
}

T_node FIND_node(T_node root,int val){

	if(root!=NULL){
		if(root->key==val){
			return root;
		}
		T_node found_node;
		found_node=FIND_node(root->left,val);
		if(found_node!=NULL){
			return found_node;
		}
		found_node=FIND_node(root->right,val);
		return found_node;

	}
	return NULL;
}

void print_cousins(T_node root,T_node level_node,int level_number){

	if(root==NULL){
		return;
	}
	if(level_number==2){

		if(root->left==level_node || root->right==level_node){
			return;
		}
		if(root->left!=NULL){
			is_cousin_found=1;
			printf("%d ",root->left->key);
		}
		if(root->right!=NULL){
			is_cousin_found=1;
			printf("%d ",root->right->key);
		}

	}
	else if(level_number>2){
	
		print_cousins(root->left, level_node , level_number-1);
		print_cousins(root->right, level_node , level_number-1);
	}
}

void FIND_COUSINS(struct binary_tree *T,int val){

	int level_number=FIND_LEVEL(T->root,val,1);
	T_node level_node=FIND_node(T->root,val);

	if(level_number>1){
		// printf("\n ==> %d \n",level_node->key);
		print_cousins(T->root,level_node,level_number);

	}

}

char *read_string(FILE* fp, size_t size){
	char *str;
	int ch;
	size_t len = 0;
	str =(char *)realloc(NULL, sizeof(*str)*size);//size is start size
	if(!str)return str;

	while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
		str[len++]=ch;
		if(len==size){
			str = (char *)realloc(str, sizeof(*str)*(size+=16));
			if(!str)return str;
		}
	}
	str[len++]='\0';

	return (char *)realloc(str, sizeof(*str)*len);
}

int main(){
	char ch;
	struct binary_tree T;
	T.root= NULL;
	int val;
	is_cousin_found=0;
	T_node new_node;

	char *input_str;

	input_str=read_string(stdin,10);
	

	CONVERT_TO_TREE(&(T.root),input_str,0);
	scanf("%d",&val);

	FIND_COUSINS(&T,val);
	if(!is_cousin_found){
		printf("-1");
	}

	return 0; 
}