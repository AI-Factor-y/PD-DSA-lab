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

void convert_to_bst(T_node *root , int arr[],int start ,int end )
{
	if(start<=end){
		int mid=start+(end-start)/2;

		*root=create_tree_node(arr[mid]);
		
		convert_to_bst(&((*root)->left),arr,start,mid-1);

		convert_to_bst(&((*root)->right),arr,mid+1,end);
	}

}

void PRINT(T_node root){

	if(root==NULL){
		printf("( ) ");
	}
	else{
		printf("( ");
	}

	if(root != NULL){
		printf("%d ",root->key);
		PRINT(root->left);
		PRINT(root->right);
		printf(") ");

	}
}

void inorder(T_node root){

	if(root!=NULL){

		inorder(root->left);
		printf("%d ",root->key);
		inorder(root->right);
	}
}

void LEVEL_sum(T_node root,int level,int level_sum[]){

	if(root!=NULL){
		level_sum[level]+=root->key;
		LEVEL_sum(root->left,level+1,level_sum);
		LEVEL_sum(root->right,level+1,level_sum);
	}
}

int FIND_MAX_HEIGHT(T_node root){

	if(root->left!=NULL || root->right!=NULL){

		int lheight=0,rheight=0,max_val;

		if(root->right!=NULL){
			rheight=FIND_MAX_HEIGHT(root->right);
		}
		if(root->left!=NULL){
			lheight=FIND_MAX_HEIGHT(root->left);
		}	

		if(lheight>rheight){
			max_val=lheight;
		}
		else{
			max_val=rheight;
		}
		max_val++; // level start from 1
		return max_val;

	}

	return 0;
}

int main(){
	char ch;
	struct binary_tree T;
	T.root= NULL;
	int val;
	int max_height=0;
	T_node new_node;

	int n;
	scanf("%d",&n);	

	if(n==0){
		return 0;
	}

	int arr[n];
	int level_sum[100000];
	for(int i=0;i<100000;i++){
		level_sum[i]=0;
	}

	for(int i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}

	convert_to_bst(&(T.root),arr,0,n-1);

	PRINT(T.root);

	max_height=FIND_MAX_HEIGHT(T.root);
	
	LEVEL_sum(T.root,1,level_sum);
	printf("\n");
	for(int i=1;i<=(max_height+1);i++){
		printf("%d ",level_sum[i]);
	}

	return 0; 
}