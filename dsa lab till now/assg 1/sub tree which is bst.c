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

int is_bst(T_node root){

	if(root==NULL){
		return 1;
	}
	if(root->left!=NULL){
		if(root->key < root->left->key){
			return 0;
		}
	}
	if(root->right!=NULL){
		if(root->key > root->right->key){
			return 0;
		}
	}
	
	return is_bst(root->left) && is_bst(root->right);

}

int find_sum(T_node root){

	if(root==NULL){
		return 0;
	}

	return root->key+find_sum(root->left)+find_sum(root->right);	
}


int FIND_BST_SUMS(T_node root,int sum){

	// int sum_val=find_sum(T);
	int sum_bst;
	if(root==NULL){
		return 0;
	}
	if(is_bst(root)){
		
		sum_bst=find_sum(root);
		
		if(sum_bst==sum){
			return 1+FIND_BST_SUMS(root->left,sum)+FIND_BST_SUMS(root->right,sum);
		}
	}
	
	return FIND_BST_SUMS(root->left,sum)+FIND_BST_SUMS(root->right,sum);
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
	int sum;

	T_node new_node;

	char *input_str;

	input_str=read_string(stdin,10);

	CONVERT_TO_TREE(&(T.root),input_str,0);
	scanf("%d",&sum);

	int ans=FIND_BST_SUMS(T.root,sum);
	if(ans==0){
		ans=-1;
	}
	printf("%d",ans);

	return 0; 
}