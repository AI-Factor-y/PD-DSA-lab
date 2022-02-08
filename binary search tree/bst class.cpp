/*   _   _     _     _                              
    __  __ ___     ___  ___  ___  ___ _____ 
 |  \/  | _ \   | _ \/ _ \| _ )/ _ \_   _|
 | |\/| |   /_  |   / (_) | _ \ (_) || |  
 |_|  |_|_|_(_) |_|_\___/|___/\___/ |_|  
                                           */
#include<bits/stdc++.h>
#define ll long long
#define MAX 1000003
#define MOD 1000000007
#define nl cout<<"\n";
// #define int ll
#define float double

ll mini(ll a,ll b){
	if(a<b) return a;
	return b;
}

ll maxi(ll a,ll b){
	if(a>b) return a;
	return b;
}

using namespace std;


class Node{

public:
	int key;
	Node *left,*right;

	Node(int key){

		this->key=key;	
		left=NULL;
		right=NULL;
	}

};


class Bst{

public:
	Node* head;

	Bst(){
		head=NULL;
	}

	Node* createNode(int key){
		Node* new_node=new Node(key);
		return new_node;
	}

	void insert(int);
	void printBst();

	Node* arrayToBstUtil(vector<int>,int,int);
	void arrayToBst(vector<int>);

	Node* predecessor(int);
	void predecessorUtil(int,Node*,Node**);

	Node* maxNode(Node*);
	Node* minNode(Node*);

	Node* successor(int);
	void successorUtil(int,Node*,Node**);

};

void Bst::insert(int key){

	Node* root=head;
	if(root==NULL){
		head=new Node(key);
		return; 
	}
	Node* prev=NULL;
	while(root!=NULL){
		prev=root;
		if(key<root->key){
			root=root->left;
		}
		else{
			root=root->right;
		}
	}
	if(key<prev->key){
		prev->left=new Node(key);
	}
	else{
		prev->right=new Node(key);
	}
	
}

void Bst::printBst(){

	if(head==NULL) return ;

	queue<Node*> bst_queue;
	bst_queue.push(head);

	while(!bst_queue.empty()){

		Node* curr_node;
		int que_size=bst_queue.size();

		for(int i=0;i<que_size;i++){
			curr_node=bst_queue.front();
			bst_queue.pop();

			if(curr_node==NULL){
				cout<<-1<<" ";
			}	
			else{
				cout<<curr_node->key<<" ";
				
				bst_queue.push(curr_node->left);
				bst_queue.push(curr_node->right);

			}
		}

		cout<<endl;

	}

}

Node* Bst::arrayToBstUtil(vector<int> arr,int start,int end){

	if(start>end) return NULL;

	int mid=start+(end-start)/2;

	Node* root=new Node(arr[mid]);
	root->left=arrayToBstUtil(arr,start,mid-1);
	root->right=arrayToBstUtil(arr,mid+1,end);

	return root;

}

void Bst::arrayToBst(vector<int> arr){

	int arr_size=arr.size();
	if(arr_size==0){
		return;
	}

	head=arrayToBstUtil(arr,0,arr_size-1);

}

Node* Bst::maxNode(Node* root){

	if(root==NULL) return NULL;

	while(root->right!=NULL){
		root=root->right;
	}

	return root;

}


void Bst::predecessorUtil(int key,Node* root,Node** pred){

	if(root==NULL){
		return;
	}
	if(root->key==key){
		if(root->left!=NULL){
			(*pred)=maxNode(root->left);
		}
		return;
	}
	if(key<root->key){
		predecessorUtil(key,root->left,pred);
	}
	else{
		(*pred)=root;
		predecessorUtil(key,root->right,pred);
	}
}

Node* Bst::predecessor(int key){
	Node* pred=NULL;
	predecessorUtil(key,head,&pred);
	return pred;
}

Node* Bst::minNode(Node* root){
	if(root==NULL) return NULL;

	while(root->left!=NULL){
		root=root->left;
	}
	return root;
}


void Bst::successorUtil(int key,Node* root,Node** success){
	if(root==NULL) return;

	if(root->key==key){
		if(root->right!=NULL)
		(*success)=minNode(root->right);
		
		return;
	}

	if(key<root->key){
		(*success)=root;
		successorUtil(key,root->left,success);
	}
	else{
		successorUtil(key,root->right,success);
	}

}

Node* Bst::successor(int key){
	Node* success=NULL;
	successorUtil(key,head,&success);
	return success;
}

void solve(){
	int temp;
		
	Bst B;
	int n=10;
	vector<int> s;
	for(int i=1;i<=n;i++){
		s.push_back(i);
	}

	B.arrayToBst(s);

	B.printBst();

	nl;
	cout<<B.predecessor(10)->key;nl;
	cout<<B.successor(9)->key;nl;
}	

signed main(){
		ios_base::sync_with_stdio(false);
	    cin.tie(NULL);
	    cout.tie(0);
		int t=1; 
		
		cin>>t;
		 
		while(t--){
			solve();

		}
		
		return 0;
}