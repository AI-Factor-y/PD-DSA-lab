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

T_node BUILD_TREE(char* str)
{ 
    int key = 0;
    int temp = 0;
    
    if(*str == '(')
    {
        str += 2;
        if(*str == ')')
        {
            return NULL;
        }
        
        while(*str >= '0' && *str <= '9')
        {
            key = key*10 + (*str - 48);
            str++;
        }

        T_node node = create_tree_node(key);
        
        str++; 
        
        node->left = BUILD_TREE(str);
        str++;

        temp = 1;
        while(temp != 0)
        {
            if(*str == '(')
                temp++;
            if(*str == ')')
                temp--;
            str++;
        }

        str++;
        node -> right = BUILD_TREE(str);
        
        return node;   
    }
    return NULL;   
}

int count(T_node root,int k,int level,int *occur){

	if(root!=NULL){
		if(root->key==k){
			printf("%d ",level);
			(*occur)++;
		}
		int level_val;
		level_val=count(root->left,k,level+1,occur);

		level_val=count(root->right,k,level+1,occur);

		return (*occur);

	}
	return (*occur);
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

	T_node new_node;
	int occur=0;

	char *input_str;

	input_str=read_string(stdin,10);
	

	T.root=BUILD_TREE(input_str);
	
	scanf("%d",&val);

	int ans=count(T.root,val,0,&occur);
		
	printf("\n%d",ans);

	return 0; 
}