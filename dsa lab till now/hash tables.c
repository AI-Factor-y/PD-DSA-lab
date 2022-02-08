#include<stdio.h>
#include<stdlib.h>

struct HTable{

	int *table;
	int size;
	int *used_space;
	char hash_type; // hash table type a for quadratic 
				// b for double hashing

	// c1 , c2 for quadratic probing
	int c1;
	int c2;

	// R for double hashing
	int R;

};


int is_prime(int n){

	if(n==1 || n==0) return 0;

	if(n<=3) return 1;

	if(n%2==0) return 0;

	if(n%3==0) return 0;

	for(int i=5;i*i<=n;i+=6){

		if((n%i==0) || (n%(i+2)==0)){
			return 0;
		}

	}

	return 1;



}



int find_near_prime(int m){

	for(int i=m-1;i>=2;i--){
		if(is_prime(i)==1){
			return i;
		}
	}
	return 1;
}

struct HTable HashTable(int m){
	struct HTable H_table_q;

	// initialising quadratic prob table
	// seting up the table , allocating space 
	H_table_q.size=m;
	H_table_q.table=(int *)malloc(m*sizeof(int));
	H_table_q.used_space=(int *)malloc(m*sizeof(int));

	for(int i=0;i<m;i++){
		H_table_q.table[i]=-1;
		H_table_q.used_space[i]=-1;
	}

	H_table_q.R=find_near_prime(m);

	return H_table_q;
}

void INSERT(struct HTable *HT,int k){

	if(HT->hash_type=='a'){

		int hash_value = k % (HT->size);
		int hash_q_val;
		for(int i=0;i<HT->size;i++){

			hash_q_val = (hash_value + (HT->c1)*i + (HT->c2)*i*i)%(HT->size);

			if( HT->used_space[hash_q_val]==-1 ){
				HT->table[hash_q_val]=k;
				HT->used_space[hash_q_val]=1;

				return;
			}
		}
	}
	else if(HT->hash_type=='b'){
		int hash_value1 = k % (HT->size);

		int hash_value2 = HT->R - ( HT->size % HT->R);

		int hash_q_val;
		for(int i=0;i<HT->size;i++){

			hash_q_val = (hash_value1 + i*hash_value2)%(HT->size);

			if( HT->used_space[hash_q_val]==-1 ){
				HT->table[hash_q_val]=k;
				HT->used_space[hash_q_val]=1;
				return;
			}
		}

	}

}


int SEARCH(struct HTable *HT,int k){

	if(HT->hash_type=='a'){
		int hash_value = k % (HT->size);
		int hash_q_val;

		for(int i=0;i<HT->size;i++){
			hash_q_val = (hash_value + (HT->c1)*i + (HT->c2)*i*i)%(HT->size);

			if( HT->table[hash_q_val]==k ){
				return 1;

			}
		}
	}
	else if(HT->hash_type=='b'){

		int hash_value1 = k % (HT->size);

		int hash_value2 = HT->R - ( HT->size % HT->R);

		int hash_q_val;
		for(int i=0;i<HT->size;i++){

			hash_q_val = (hash_value1 + i*hash_value2)%(HT->size);

			if( HT->table[hash_q_val]==k ){
				
				return 1;
			}
		}


	}

	return -1;
}

void DELETE(struct HTable *HT,int k){

	if(HT->hash_type=='a'){
		int hash_value = k % (HT->size);
		int hash_q_val;

		for(int i=0;i<HT->size;i++){
			hash_q_val = (hash_value + (HT->c1)*i + (HT->c2)*i*i)%(HT->size);

			if( HT->table[hash_q_val]==k ){
				HT->table[hash_q_val]=-1;
				HT->used_space[hash_q_val]=-1;
				return;

			}
		}
	
	}
	else if(HT->hash_type=='b'){

		int hash_value1 = k % (HT->size);

		int hash_value2 = HT->R - ( HT->size % HT->R);

		int hash_q_val;
		for(int i=0;i<HT->size;i++){

			hash_q_val = (hash_value1 + i*hash_value2)%(HT->size);

			if( HT->table[hash_q_val]==k ){
				HT->table[hash_q_val]=-1;
				HT->used_space[hash_q_val]=-1;
				return;
			}
		}


	}

	
}


void PRINT(struct HTable *HT ){

	for(int i=0;i<HT->size;i++){
		if(HT->table[i]!=-1){
			printf("%d (%d)\n",i,HT->table[i]);
		}
		else{
			printf("%d ()\n",i);
		}

	}

}

int main(){

	struct HTable HT;

	char hash_type,ch;
	int m;
	int c1,c2;
	scanf("%c",&hash_type);

	// read size of hash table
	scanf("%d",&m);

	// create a hashtable
	HT=HashTable(m);
	HT.hash_type=hash_type;

	if(hash_type=='a'){

		scanf("%d",&c1);
		scanf("%d",&c2);
		//setting coef for quad prob
		HT.c1=c1;
		HT.c2=c2;

	}
	
	// variables for table values
	int val;
	int search_result;


	do{	
		scanf("%c",&ch);

		switch(ch){

			case 'i':
				scanf("%d",&val);

				INSERT(&HT,val);

				break;

			case 's':
				scanf("%d",&val);
				search_result=SEARCH(&HT,val);
				printf("%d\n",search_result);
				break;

			case 'd':	
				scanf("%d",&val);
				DELETE(&HT,val);
				break;

			case 'p':
				PRINT(&HT);
				break;

		}

	}while(ch!='t');


	return 0;
}