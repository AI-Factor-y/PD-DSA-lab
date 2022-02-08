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

void TRANSPLANT(struct bst *T,T_node u,T_node v){

	if(u->parent==NULL){
		T->root=v;
	}
	else if(u== u->parent->left){
		u->parent->left = v;
	}
	else{
		u->parent->right = v;
	}
	if(v != NULL){
		v->parent = u->parent;
	}

}

T_node TREE_MINIMUM(T_node root){

	T_node x=root;
	while(root->left!=NULL){
		root=root->left;
	}
	return root;
}

void DELETE(struct bst *T, T_node z){

	if(z->left==NULL){
		TRANSPLANT(T, z, z->right);
	}
	else if(z->right == NULL){
		TRANSPLANT(T,z,z->left);
	}
	else{

		T_node y=TREE_MINIMUM(z->right);

		if(y->parent != z){
			TRANSPLANT(T,y,y->right);
			y->right =z->right;
			y->right->parent = y;
		}

		TRANSPLANT(T,z,y);
		y->left=z->left;
		y->left->parent=y;

	}
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

int LEVEL(struct bst *T,int key){

	int level_val=FIND_LEVEL(T->root,key,1);
	if(level_val==0){
		level_val=-1;
	}

	return level_val;

}

T_node Successor(struct bst *T,T_node x){

	T_node root=x;

	if(root->right!=NULL){
		return TREE_MINIMUM(root->right);
	}
	T_node y=root->parent;

	while(y!=NULL && x==y->right){
		x=y;
		y=y->parent;
	}
	return y;
}

T_node Predecessor(struct bst *T,T_node x){

	T_node root=x;

	if(root->left!=NULL){
		return MAX_VALUE(root->left);
	}
	T_node y=root->parent;

	while(y!=NULL && x==y->left){
		x=y;
		y=y->parent;
	}
	return y;
}



int main(){

	char ch;
	struct bst T;
	T.root= NULL;
	int val;
	T_node min_val,max_val;
	int level_val;
	T_node new_node,search_node,delete_node,s_node,p_node;

	do{
		scanf("%c",&ch);

		switch(ch){

			case 'a':
				scanf("%d",&val);
				new_node = create_tree_node(val);
				INSERT(&T,new_node);
				break;

			case 'd':
				scanf("%d",&val);
				search_node=create_tree_node(val);
				delete_node=SEARCH(&T,search_node);

				if(delete_node!=NULL){
					DELETE(&T,delete_node);
					printf("%d\n",val);
				}
				else{
					printf("%d\n",-1);
				}
				break;

			case 's':
				scanf("%d",&val);
				search_node=create_tree_node(val);
				if(SEARCH(&T,search_node)!=NULL){
					printf("%d\n",1);
				}
				else{
					printf("%d\n",-1);
				}
				break;
	
			case 'l':
				// find level for the node
				scanf("%d",&val);

				level_val=LEVEL(&T,val);
				printf("%d\n",level_val);
				break;

			case 'm':
				min_val=MIN_VALUE(T.root);
				printf("%d\n",min_val->key);
				break;

			case 'x':
				max_val=MAX_VALUE(T.root);
				printf("%d\n",max_val->key);
				break;

			case 'r':

				scanf("%d",&val);

				new_node=create_tree_node(val);
				search_node=SEARCH(&T,new_node);
				if(search_node==NULL){
					printf("-1\n");
				}
				else{
					s_node=Predecessor(&T,search_node);
					if(s_node==NULL){
						printf("-1\n");
					}
					else{
						printf("%d\n",s_node->key);
					}
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
					s_node=Successor(&T,search_node);
					if(s_node==NULL){
						printf("-1\n");
					}
					else{
						printf("%d\n",s_node->key);
					}
				}

				break;	

			case 'i':
				INORDER(T.root);
				printf("\n");
				break;

			case 'p':
				PREORDER(T.root);
				printf("\n");
				break;

			case 't':
				POSTORDER(T.root);
				printf("\n");
				break;


			
		}

	}while(ch!='e');



	return 0;
}