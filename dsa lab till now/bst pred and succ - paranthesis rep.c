#include<stdio.h>
#include<stdlib.h>

struct Tree{
	int key;
	struct Tree *left,*right;

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

	return temp;
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

T_node SEARCH(struct bst *T,T_node k){
	T_node x=T->root;

	while(x!=NULL && k->key != x->key){

		if(k->key > x->key){
			x=x->right;
		}
		else{
			x=x->left;
		}

	}

	return x;
}


T_node TREE_MINIMUM(T_node root){

	T_node x=root;
	while(root->left!=NULL){
		root=root->left;
	}
	return root;
}


T_node MIN_VALUE(T_node x){

	while(x->left!=NULL){
		x=x->left;
	}
	return x;
}

T_node MAX_VALUE(T_node x){

	while(x->right!=NULL){
		x=x->right;
	}

	return x;
}


int *inorder_arr;
int inorder_array_size=0;
int inorder_count=0;
void inorder_array_create(T_node root){

	if(root!=NULL){

		inorder_array_create(root->left);

		if(inorder_array_size==inorder_count){
			inorder_arr=(int *)realloc(inorder_arr, sizeof(*inorder_arr)*(inorder_array_size*=2));
		}
		inorder_arr[inorder_count++]=root->key;
		inorder_array_create(root->right);

	}

}

void inorder_array_caller(T_node root){
	inorder_array_size=2;
	inorder_count=0;
	inorder_arr=(int *)malloc(sizeof(int)*inorder_array_size);
	inorder_array_create(root);
}

int Successor(struct bst *T,T_node x){

	inorder_array_caller(T->root);
	int pos=-1;
	for(int i=0;i<inorder_count;i++){
		if(inorder_arr[i]==x->key){
			pos=i;
			break;
		}
	}
	int ans=-1;

	if(pos==-1){
		return -1;
	}

	if(pos!=(inorder_count-1)){
		ans=inorder_arr[pos+1];
	}
	return ans;

}

int Predecessor(struct bst *T,T_node x){

	inorder_array_caller(T->root);
	int pos=-1;
	for(int i=0;i<inorder_count;i++){
		if(inorder_arr[i]==x->key){
			pos=i;
			break;
		}
	}
	int ans=-1;
	if(pos==-1){
		return -1;
	}
	if(pos!=0){
		ans=inorder_arr[pos-1];
	}
	return ans;
}
//-------------------- 


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

	if(k_smallest_node==NULL){
		return -1;
	}

	return k_smallest_node->key;

}

int curr_largest=0;
T_node inorder_largest(T_node root,int k){
	T_node ret_Val;
	if(root!=NULL){
		ret_Val=inorder_largest(root->right,k);
		if(ret_Val!=NULL){
			return ret_Val;
		}
		curr_largest++;
		
		if(k==curr_largest){
			return root;
		}
		
		ret_Val=inorder_largest(root->left,k);
		if(ret_Val!=NULL){
			return ret_Val;
		}
	}
	return NULL;
}



int KLargest(T_node root,int k){

	curr_largest=0;

	T_node k_largest_node=inorder_largest(root,k);

	if(k_largest_node==NULL){
		return -1;
	}

	return k_largest_node->key;

}





int main(){

	char ch;
	struct bst T;
	T.root= NULL;
	int val;
	T_node min_val,max_val;
	int level_val;
	T_node new_node,search_node,delete_node,s_node,p_node;

	//---------
	char *input_str;

	input_str=read_string(stdin,10);

	CONVERT_TO_TREE(&(T.root),input_str,0);

	


	do{
		scanf("%c",&ch);

		switch(ch){

			case 'r':

				scanf("%d",&val);

				new_node=create_tree_node(val);
				search_node=SEARCH(&T,new_node);
				if(search_node==NULL){
					printf("-1\n");
				}
				else{
					printf("%d\n",Predecessor(&T,search_node));
				}

				break;	


			case 'u':

				scanf("%d",&val);

				new_node=create_tree_node(val);
				search_node=SEARCH(&T,new_node);
				if(search_node==NULL){
					printf("-1\n");
				}
				else{
					printf("%d\n",Successor(&T,search_node));
				}

				break;	

			case 'i':
				INORDER(T.root);
				printf("\n");
				break;

			case 'l':
				scanf("%d",&val);
				printf("%d\n",KLargest(T.root,val));
				break;

			case 's':
				scanf("%d",&val);
				printf("%d\n",KSmallest(T.root,val));
			
		}

	}while(ch!='e');



	return 0;
}