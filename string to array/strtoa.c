#include<stdio.h>
#include<stdlib.h>

struct Tree{
	int key;
	struct Tree *left,*right,*parent;

};

// typedef and create a type *linked_list

typedef struct Tree *T_node;

struct bst{
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

void INSERT(struct bst *T, T_node z){

	T_node y=NULL;
	T_node x=T->root;

	while(x != NULL){
		y=x;

		if(z->key < x->key){
			x=x->left;
		}
		else{
			x=x->right;
		}
	}
	z->parent=y;
	if(y==NULL){
		T->root=z;
	}
	else if(z->key < y->key){
		y->left = z;
	}
	else{
		y->right=z;
	}

}

void INORDER(T_node root){

	if(root != NULL){
		INORDER(root->left);
		printf("%d ",root->key);
		INORDER(root->right);
	}

}

void PREORDER(T_node root){

	if(root != NULL){
		printf("%d ",root->key);
		PREORDER(root->left);
		PREORDER(root->right);
	}

}

void POSTORDER(T_node root){

	if(root != NULL){
		POSTORDER(root->left);
		POSTORDER(root->right);
		printf("%d ",root->key);
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

int *conv_stoa(char *str,int *array_len){

	int *arr;	
	int size=2;
	arr=(int *)realloc(NULL,size*sizeof(*arr));

	int index=0;
	*array_len=0;
	int num=0,is_neg=1;
	int i=0;
	int no_num=1;
	while(1){

		if(str[i]=='-'){
			is_neg=-1;
		}
		else if(str[i]>='0' && str[i]<='9'){
			num=num*10 + (str[i]-'0');
			no_num=0;
		}
		else{

			if(size==index){
				arr=(int *)realloc(arr,sizeof(*arr)*(size*=2));
			}
			arr[index]=is_neg*num;
			
			num=0;
			is_neg=1;
			index++;
			(*array_len)++;
		}

		if(str[i]=='\0'){
			break;
		}

		i++;

	}
	if(no_num==1){
		(*array_len)=0;
	}
	return (int *)realloc(arr,size*sizeof(*arr));
}

int main(){

	char ch;
	struct bst T;
	T.root= NULL;
	int val,len=0;

	int *arr;

	T_node new_node;

	char *input_str;
	input_str=read_string(stdin,10);

	arr=conv_stoa(input_str,&len);

	for(int i=0;i<len;i++){
		printf("%d ",arr[i]);
	}


	return 0;
}