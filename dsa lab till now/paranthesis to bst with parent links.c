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

void SET_TREE_PARENTS(T_node *root,T_node p){
	if((*root)!=NULL){

		SET_TREE_PARENTS(&((*root)->left),*root);
		(*root)->parent = p;

		SET_TREE_PARENTS(&((*root)->right),*root);
	}
}

void CONV_TO_BST(T_node *root ,char *str,int start){

	CONVERT_TO_TREE(root,str,start);

	SET_TREE_PARENTS(root,NULL);

}

int curr_smallest=0;
T_node inorder_smallest(T_node root,int k){
	T_node ret_Val;
	if(root!=NULL){
		ret_Val=inorder_smallest(root->left,k);
		if(ret_Val!=NULL){
			return ret_Val;
		}
		curr_smallest++;
		
		if(k==curr_smallest){
			return root;
		}
		
		ret_Val=inorder_smallest(root->right,k);
		if(ret_Val!=NULL){
			return ret_Val;
		}
	}
	return NULL;
}



int KSmallest(T_node root,int k){

	curr_smallest=0;

	T_node k_smallest_node=inorder_smallest(root,k);

	return k_smallest_node->key;

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

	CONV_TO_BST(&(T.root),input_str,0);
	scanf("%d",&val);

	printf("%d",KSmallest(T.root,val));


	return 0; 
}