
#include<bits/stdc++.h>

using namespace std;

const int ORDER= 4;


typedef struct node {
	struct node *parent;
	bool is_leaf;
	int nKeys;
	int levelVal;
	void **childrens;
	int *keys;
	struct node *next;
} node;


typedef struct record {
	int value;
} record;


int order = ORDER;
node *QUEUE = NULL;
bool verbose_output = false;

void find_and_print_range(node *const root, int range1, int range2, bool verbose);
int find_range(node *const root, int key_start, int key_end, bool verbose,
		 int returned_keys[], void *returned_childrens[]);
node *find_leaf(node *const root, int key, bool verbose);
record *find(node *root, int key, bool verbose, node **leaf_out);
int cut(int length);
void enQUEUE(node *new_node);
node *deQUEUE(void);
int height(node *const root);
int path_to_root(node *const root, node *child);
void print_leaves(node *const root);
void print_tree(node *const root);
void find_and_print(node *const root, int key, bool verbose);
record *make_record(int value);
node *make_node(void);
node *make_leaf(void);
int get_left_index(node *parent, node *left);
node *insert_into_leaf(node *leaf, int key, record *pointer);
node *insert_into_leaf_after_splitting(node *root, node *leaf, int key,
					 record *pointer);
node *insert_into_node(node *root, node *parent,
			 int left_index, int key, node *right);
node *insert_into_node_after_splitting(node *root, node *parent,
					 int left_index,
					 int key, node *right);
node *insert_into_parent(node *root, node *left, int key, node *right);
node *insert_into_new_root(node *left, int key, node *right);
node *start_new_tree(int key, record *pointer);
node *insert(node *root, int key, int value);

int get_neighbor_index(node *n);
node *adjust_root(node *root);
node *coalesce_nodes(node *root, node *n, node *neighbor,
			 int neighbor_index, int k_prime);
node *redistribute_nodes(node *root, node *n, node *neighbor,
			 int neighbor_index,
			 int k_prime_index, int k_prime);
node *delete_entry(node *root, node *n, int key, void *pointer);
node *delete_key(node *root, int key);

void enQUEUE(node *new_node) {
	node *c;
	if (QUEUE == NULL) {
	QUEUE = new_node;
	QUEUE->next = NULL;
	} else {
	c = QUEUE;
	while (c->next != NULL) {
		c = c->next;
	}
	c->next = new_node;
	new_node->next = NULL;
	}
}

node *deQUEUE(void) {
	node *n = QUEUE;
	QUEUE = QUEUE->next;
	n->next = NULL;
	return n;
}

void print_leaves(node *const root) {
	if (root == NULL) {
	printf("Empty tree.\n");
	return;
	}
	int i;
	node *c = root;
	while (!c->is_leaf)
	c =(node *)c->childrens[0];
	while (true) {
	for (i = 0; i < c->nKeys; i++) {
		if (verbose_output)
		printf("%p ", c->childrens[i]);
		printf("%d ", c->keys[i]);
	}
	if (verbose_output)
		printf("%p ", c->childrens[order - 1]);
	if (c->childrens[order - 1] != NULL) {
		printf(" | ");
		c =(node *)c->childrens[order - 1];
	} else
		break;
	}
	printf("\n");
}

int height(node *const root) {
	int h = 0;
	node *c = root;
	while (!c->is_leaf) {
	c = (node*)c->childrens[0];
	h++;
	}
	return h;
}
int path_to_root(node *const root, node *child) {
	int length = 0;
	node *c = child;
	while (c != root) {
	c = c->parent;
	length++;
	}
	return length;
}

void print_tree(node *root) {
	node *n = NULL;
	int i = 0;
	int rank = 0;
	int new_rank = 0;

	if (root == NULL) {
	printf("Empty tree.\n");
	return;
	}
	root->levelVal=1;
	QUEUE = NULL;
	enQUEUE(root);
	while (QUEUE != NULL) {
		n = deQUEUE();
		if (n->parent != NULL && n == n->parent->childrens[0]) {
			new_rank = path_to_root(root, n);
			if (new_rank != rank) {
			rank = new_rank;
		
			}
		}
		
		for (i = 0; i < n->nKeys; i++) {
			printf("%d ", n->keys[i]);
		}
		if (!n->is_leaf)
			for (i = 0; i <= n->nKeys; i++)
			{	enQUEUE((node*)n->childrens[i]);
				if((node*)n->childrens[i]!=NULL){
					node* childNode=(node*)n->childrens[i];
					childNode->levelVal=(n->levelVal)+1;
				}
			}
	}
	printf("\n");
}

void find_and_print(node *const root, int key, bool verbose) {
	node *leaf = NULL;
	record *r = find(root, key, verbose, NULL);
	if (r == NULL)
	printf("Record not found under key %d.\n", key);
	else
	printf("Record at %p -- key %d, value %d.\n",
		 r, key, r->value);
}

void find_and_print_range(node *const root, int key_start, int key_end,
				bool verbose) {
	int i;
	int array_size = key_end - key_start + 1;
	int returned_keys[array_size];
	void *returned_childrens[array_size];
	int num_found = find_range(root, key_start, key_end, verbose,
				 returned_keys, returned_childrens);
	if (!num_found)
	printf("None found.\n");
	else {
	for (i = 0; i < num_found; i++)
		printf("Key: %d   Location: %p  Value: %d\n",
			 returned_keys[i],
			 returned_childrens[i],
			 ((record *)
			returned_childrens[i])
			 ->value);
	}
}

int find_range(node *const root, int key_start, int key_end, bool verbose,
		 int returned_keys[], void *returned_childrens[]) {
	int i, num_found;
	num_found = 0;
	node *n = find_leaf(root, key_start, verbose);
	if (n == NULL)
	return 0;
	for (i = 0; i < n->nKeys && n->keys[i] < key_start; i++)
	;
	if (i == n->nKeys)
	return 0;
	while (n != NULL) {
	for (; i < n->nKeys && n->keys[i] <= key_end; i++) {
		returned_keys[num_found] = n->keys[i];
		returned_childrens[num_found] = n->childrens[i];
		num_found++;
	}
	n = (node *)n->childrens[order - 1];
	i = 0;
	}
	return num_found;
}

node *find_leaf(node *const root, int key, bool verbose) {
	if (root == NULL) {
	if (verbose)
		printf("Empty tree.\n");
	return root;
	}
	int i = 0;
	node *c = root;
	while (!c->is_leaf) {
	if (verbose) {
		printf("[");
		for (i = 0; i < c->nKeys - 1; i++)
		printf("%d ", c->keys[i]);
		printf("%d] ", c->keys[i]);
	}
	i = 0;
	while (i < c->nKeys) {
		if (key >= c->keys[i])
		i++;
		else
		break;
	}
	if (verbose)
		printf("%d ->\n", i);
	c = (node *)c->childrens[i];
	}
	if (verbose) {
	printf("Leaf [");
	for (i = 0; i < c->nKeys - 1; i++)
		printf("%d ", c->keys[i]);
	printf("%d] ->\n", c->keys[i]);
	}
	return c;
}

record *find(node *root, int key, bool verbose, node **leaf_out) {
	if (root == NULL) {
	if (leaf_out != NULL) {
		*leaf_out = NULL;
	}
	return NULL;
	}

	int i = 0;
	node *leaf = NULL;

	leaf = find_leaf(root, key, verbose);

	for (i = 0; i < leaf->nKeys; i++)
	if (leaf->keys[i] == key)
		break;
	if (leaf_out != NULL) {
	*leaf_out = leaf;
	}
	if (i == leaf->nKeys)
	return NULL;
	else
	return (record *)leaf->childrens[i];
}

int cut(int length) {
	if (length % 2 == 0)
	return length / 2;
	else
	return length / 2 + 1;
}

record *make_record(int value) {
	record *new_record = (record *)malloc(sizeof(record));
	if (new_record == NULL) {
	perror("Record creation.");
	exit(EXIT_FAILURE);
	} else {
	new_record->value = value;
	}
	return new_record;
}

node *make_node(void) {
	node *new_node;
	new_node =(node *)malloc(sizeof(node));
	if (new_node == NULL) {
	perror("Node creation.");
	exit(EXIT_FAILURE);
	}
	new_node->keys =(int*)malloc((order - 1) * sizeof(int));
	if (new_node->keys == NULL) {
	perror("New node keys array.");
	exit(EXIT_FAILURE);
	}
	new_node->childrens = (void**)malloc(order * sizeof(void *));
	if (new_node->childrens == NULL) {
	perror("New node childrens array.");
	exit(EXIT_FAILURE);
	}
	new_node->is_leaf = false;
	new_node->nKeys = 0;
	new_node->parent = NULL;
	new_node->next = NULL;
	return new_node;
}

node *make_leaf(void) {
	node *leaf = make_node();
	leaf->is_leaf = true;
	return leaf;
}

int get_left_index(node *parent, node *left) {
	int left_index = 0;
	while (left_index <= parent->nKeys &&
		 parent->childrens[left_index] != left)
	left_index++;
	return left_index;
}

node *insert_into_leaf(node *leaf, int key, record *pointer) {
	int i, insertion_point;

	insertion_point = 0;
	while (insertion_point < leaf->nKeys && leaf->keys[insertion_point] < key)
	insertion_point++;

	for (i = leaf->nKeys; i > insertion_point; i--) {
	leaf->keys[i] = leaf->keys[i - 1];
	leaf->childrens[i] = leaf->childrens[i - 1];
	}
	leaf->keys[insertion_point] = key;
	leaf->childrens[insertion_point] = pointer;
	leaf->nKeys++;
	return leaf;
}

node *insert_into_leaf_after_splitting(node *root, node *leaf, int key, record *pointer) {
	node *new_leaf;
	int *temp_keys;
	void **temp_childrens;
	int insertion_index, split, new_key, i, j;

	new_leaf = make_leaf();

	temp_keys = (int*)malloc(order * sizeof(int));
	if (temp_keys == NULL) {
	perror("Temporary keys array.");
	exit(EXIT_FAILURE);
	}

	temp_childrens = (void**)malloc(order * sizeof(void *));
	if (temp_childrens == NULL) {
	perror("Temporary childrens array.");
	exit(EXIT_FAILURE);
	}

	insertion_index = 0;
	while (insertion_index < order - 1 && leaf->keys[insertion_index] < key)
	insertion_index++;

	for (i = 0, j = 0; i < leaf->nKeys; i++, j++) {
	if (j == insertion_index)
		j++;
	temp_keys[j] = leaf->keys[i];
	temp_childrens[j] = leaf->childrens[i];
	}

	temp_keys[insertion_index] = key;
	temp_childrens[insertion_index] = pointer;

	leaf->nKeys = 0;

	split = cut(order - 1);

	for (i = 0; i < split; i++) {
	leaf->childrens[i] = temp_childrens[i];
	leaf->keys[i] = temp_keys[i];
	leaf->nKeys++;
	}

	for (i = split, j = 0; i < order; i++, j++) {
	new_leaf->childrens[j] = temp_childrens[i];
	new_leaf->keys[j] = temp_keys[i];
	new_leaf->nKeys++;
	}

	free(temp_childrens);
	free(temp_keys);

	new_leaf->childrens[order - 1] = leaf->childrens[order - 1];
	leaf->childrens[order - 1] = new_leaf;

	for (i = leaf->nKeys; i < order - 1; i++)
	leaf->childrens[i] = NULL;
	for (i = new_leaf->nKeys; i < order - 1; i++)
	new_leaf->childrens[i] = NULL;

	new_leaf->parent = leaf->parent;
	new_key = new_leaf->keys[0];

	return insert_into_parent(root, leaf, new_key, new_leaf);
}

node *insert_into_node(node *root, node *n,
			 int left_index, int key, node *right) {
	int i;

	for (i = n->nKeys; i > left_index; i--) {
	n->childrens[i + 1] = n->childrens[i];
	n->keys[i] = n->keys[i - 1];
	}
	n->childrens[left_index + 1] = right;
	n->keys[left_index] = key;
	n->nKeys++;
	return root;
}

node *insert_into_node_after_splitting(node *root, node *old_node, int left_index,
					 int key, node *right) {
	int i, j, split, k_prime;
	node *new_node, *child;
	int *temp_keys;
	node **temp_childrens;

	temp_childrens = (node**)malloc((order + 1) * sizeof(node *));
	if (temp_childrens == NULL) {
	perror("Temporary childrens array for splitting nodes.");
	exit(EXIT_FAILURE);
	}
	temp_keys = (int*)malloc(order * sizeof(int));
	if (temp_keys == NULL) {
	perror("Temporary keys array for splitting nodes.");
	exit(EXIT_FAILURE);
	}

	for (i = 0, j = 0; i < old_node->nKeys + 1; i++, j++) {
	if (j == left_index + 1)
		j++;
	temp_childrens[j] = (node*)old_node->childrens[i];
	}

	for (i = 0, j = 0; i < old_node->nKeys; i++, j++) {
	if (j == left_index)
		j++;
	temp_keys[j] = old_node->keys[i];
	}

	temp_childrens[left_index + 1] = right;
	temp_keys[left_index] = key;

	split = cut(order);
	new_node = make_node();
	old_node->nKeys = 0;
	for (i = 0; i < split - 1; i++) {
	old_node->childrens[i] = temp_childrens[i];
	old_node->keys[i] = temp_keys[i];
	old_node->nKeys++;
	}
	old_node->childrens[i] = temp_childrens[i];
	k_prime = temp_keys[split - 1];
	for (++i, j = 0; i < order; i++, j++) {
	new_node->childrens[j] = temp_childrens[i];
	new_node->keys[j] = temp_keys[i];
	new_node->nKeys++;
	}
	new_node->childrens[j] = temp_childrens[i];
	free(temp_childrens);
	free(temp_keys);
	new_node->parent = old_node->parent;
	for (i = 0; i <= new_node->nKeys; i++) {
	child = (node*)new_node->childrens[i];
	child->parent = new_node;
	}

	return insert_into_parent(root, old_node, k_prime, new_node);
}

node *insert_into_parent(node *root, node *left, int key, node *right) {
	int left_index;
	node *parent;

	parent = left->parent;

	if (parent == NULL)
	return insert_into_new_root(left, key, right);

	left_index = get_left_index(parent, left);

	if (parent->nKeys < order - 1)
	return insert_into_node(root, parent, left_index, key, right);

	return insert_into_node_after_splitting(root, parent, left_index, key, right);
}

node *insert_into_new_root(node *left, int key, node *right) {
	node *root = make_node();
	root->keys[0] = key;
	root->childrens[0] = left;
	root->childrens[1] = right;
	root->nKeys++;
	root->parent = NULL;
	left->parent = root;
	right->parent = root;
	return root;
}

node *start_new_tree(int key, record *pointer) {
	node *root = make_leaf();
	root->keys[0] = key;
	root->childrens[0] = pointer;
	root->childrens[order - 1] = NULL;
	root->parent = NULL;
	root->nKeys++;
	return root;
}

node *insert(node *root, int key, int value) {
	record *record_pointer = NULL;
	node *leaf = NULL;

	record_pointer = find(root, key, false, NULL);
	if (record_pointer != NULL) {
	record_pointer->value = value;
	return root;
	}

	record_pointer = make_record(value);

	if (root == NULL)
	return start_new_tree(key, record_pointer);

	leaf = find_leaf(root, key, false);

	if (leaf->nKeys < order - 1) {
	leaf = insert_into_leaf(leaf, key, record_pointer);
	return root;
	}

	return insert_into_leaf_after_splitting(root, leaf, key, record_pointer);
}

int get_neighbor_index(node *n) {
	int i;
	for (i = 0; i <= n->parent->nKeys; i++)
	if (n->parent->childrens[i] == n)
		return i - 1;

	printf("Search for nonexistent pointer to node in parent.\n");
	printf("Node:  %#lx\n", (unsigned long)n);
	exit(EXIT_FAILURE);
}

node *remove_entry_from_node(node *n, int key, node *pointer) {
	int i, num_childrens;
	i = 0;
	while (n->keys[i] != key)
	i++;
	for (++i; i < n->nKeys; i++)
	n->keys[i - 1] = n->keys[i];

	num_childrens = n->is_leaf ? n->nKeys : n->nKeys + 1;
	i = 0;
	while (n->childrens[i] != pointer)
	i++;
	for (++i; i < num_childrens; i++)
	n->childrens[i - 1] = n->childrens[i];

	n->nKeys--;

	if (n->is_leaf)
	for (i = n->nKeys; i < order - 1; i++)
		n->childrens[i] = NULL;
	else
	for (i = n->nKeys + 1; i < order; i++)
		n->childrens[i] = NULL;

	return n;
}

node *adjust_root(node *root) {
	node *new_root;

	if (root->nKeys > 0)
	return root;

	if (!root->is_leaf) {
	new_root = (node*)root->childrens[0];
	new_root->parent = NULL;
	}

	else
	new_root = NULL;

	free(root->keys);
	free(root->childrens);
	free(root);

	return new_root;
}

node *coalesce_nodes(node *root, node *n, node *neighbor, int neighbor_index, int k_prime) {
	int i, j, neighbor_insertion_index, n_end;
	node *tmp;

	if (neighbor_index == -1) {
	tmp = n;
	n = neighbor;
	neighbor = tmp;
	}

	neighbor_insertion_index = neighbor->nKeys;

	if (!n->is_leaf) {
	neighbor->keys[neighbor_insertion_index] = k_prime;
	neighbor->nKeys++;

	n_end = n->nKeys;

	for (i = neighbor_insertion_index + 1, j = 0; j < n_end; i++, j++) {
		neighbor->keys[i] = n->keys[j];
		neighbor->childrens[i] = n->childrens[j];
		neighbor->nKeys++;
		n->nKeys--;
	}

	neighbor->childrens[i] = n->childrens[j];

	for (i = 0; i < neighbor->nKeys + 1; i++) {
		tmp = (node *)neighbor->childrens[i];
		tmp->parent = neighbor;
	}
	}

	else {
	for (i = neighbor_insertion_index, j = 0; j < n->nKeys; i++, j++) {
		neighbor->keys[i] = n->keys[j];
		neighbor->childrens[i] = n->childrens[j];
		neighbor->nKeys++;
	}
	neighbor->childrens[order - 1] = n->childrens[order - 1];
	}

	root = delete_entry(root, n->parent, k_prime, n);
	free(n->keys);
	free(n->childrens);
	free(n);
	return root;
}

node *redistribute_nodes(node *root, node *n, node *neighbor, int neighbor_index,
			 int k_prime_index, int k_prime) {
	int i;
	node *tmp;

	if (neighbor_index != -1) {
	if (!n->is_leaf)
		n->childrens[n->nKeys + 1] = n->childrens[n->nKeys];
	for (i = n->nKeys; i > 0; i--) {
		n->keys[i] = n->keys[i - 1];
		n->childrens[i] = n->childrens[i - 1];
	}
	if (!n->is_leaf) {
		n->childrens[0] = neighbor->childrens[neighbor->nKeys];
		tmp = (node *)n->childrens[0];
		tmp->parent = n;
		neighbor->childrens[neighbor->nKeys] = NULL;
		n->keys[0] = k_prime;
		n->parent->keys[k_prime_index] = neighbor->keys[neighbor->nKeys - 1];
	} else {
		n->childrens[0] = neighbor->childrens[neighbor->nKeys - 1];
		neighbor->childrens[neighbor->nKeys - 1] = NULL;
		n->keys[0] = neighbor->keys[neighbor->nKeys - 1];
		n->parent->keys[k_prime_index] = n->keys[0];
	}
	}

	else {
	if (n->is_leaf) {
		n->keys[n->nKeys] = neighbor->keys[0];
		n->childrens[n->nKeys] = neighbor->childrens[0];
		n->parent->keys[k_prime_index] = neighbor->keys[1];
	} else {
		n->keys[n->nKeys] = k_prime;
		n->childrens[n->nKeys + 1] = neighbor->childrens[0];
		tmp = (node *)n->childrens[n->nKeys + 1];
		tmp->parent = n;
		n->parent->keys[k_prime_index] = neighbor->keys[0];
	}
	for (i = 0; i < neighbor->nKeys - 1; i++) {
		neighbor->keys[i] = neighbor->keys[i + 1];
		neighbor->childrens[i] = neighbor->childrens[i + 1];
	}
	if (!n->is_leaf)
		neighbor->childrens[i] = neighbor->childrens[i + 1];
	}

	n->nKeys++;
	neighbor->nKeys--;

	return root;
}

node *delete_entry(node *root, node *n, int key, void *pointer) {
	int min_keys;
	node *neighbor;
	int neighbor_index;
	int k_prime_index, k_prime;
	int capacity;

	n = remove_entry_from_node(n, key, (node*)pointer);

	if (n == root)
	return adjust_root(root);

	min_keys = n->is_leaf ? cut(order - 1) : cut(order) - 1;

	if (n->nKeys >= min_keys)
	return root;

	neighbor_index = get_neighbor_index(n);
	k_prime_index = neighbor_index == -1 ? 0 : neighbor_index;
	k_prime = n->parent->keys[k_prime_index];
	neighbor = neighbor_index == -1 ? (node*)n->parent->childrens[1] : (node*)n->parent->childrens[neighbor_index];

	capacity = n->is_leaf ? order : order - 1;

	if (neighbor->nKeys + n->nKeys < capacity)
	return coalesce_nodes(root, n, neighbor, neighbor_index, k_prime);
	else
	return redistribute_nodes(root, n, neighbor, neighbor_index, k_prime_index, k_prime);
}


int search(node *root,int key){
	node *n = NULL;
	int i = 0;
	int rank = 0;
	int new_rank = 0;

	if (root == NULL) {
	printf("Empty tree.\n");
	return 0;
	}
	root->levelVal=1;
	QUEUE = NULL;
	enQUEUE(root);
	while (QUEUE != NULL) {
		n = deQUEUE();
		if (n->parent != NULL && n == n->parent->childrens[0]) {
			new_rank = path_to_root(root, n);
			if (new_rank != rank) {
			rank = new_rank;
		
			}
		}



		
		for (i = 0; i < n->nKeys; i++) {
			if(n->keys[i]==key){
				return n->levelVal;
			}
		}
		if (!n->is_leaf)
			for (i = 0; i <= n->nKeys; i++)
			{	enQUEUE((node*)n->childrens[i]);
				if((node*)n->childrens[i]!=NULL){
					node* childNode=(node*)n->childrens[i];
					childNode->levelVal=(n->levelVal)+1;
				}
			}
	}
	return 0;
}


node* delete_key (node *root, int key) {
	node *key_leaf = NULL;
	record *key_record = NULL;

	key_record = find(root, key, false, &key_leaf);

	if (key_record != NULL && key_leaf != NULL) {
	root = delete_entry(root, key_leaf, key, key_record);
	free(key_record);
	}
	return root;
}

void destroy_tree_nodes(node *root) {
	int i;
	if (root->is_leaf)
	for (i = 0; i < root->nKeys; i++)
		free(root->childrens[i]);
	else
	for (i = 0; i < root->nKeys + 1; i++)
		destroy_tree_nodes((node*)root->childrens[i]);
	free(root->childrens);
	free(root->keys);
	free(root);
}

node *destroy_tree(node *root) {
	destroy_tree_nodes(root);
	return NULL;
}


void print_tree_struct(node *const root) {
  node *n = NULL;
  int i = 0;
  int rank = 0;
  int new_rank = 0;
  cout<<endl;
  if (root == NULL) {
    printf("Empty tree.\n");
    return;
  }
  QUEUE = NULL;
  enQUEUE(root);
  while (QUEUE != NULL) {
    n = deQUEUE();
    if (n->parent != NULL && n == n->parent->childrens[0]) {
      new_rank = path_to_root(root, n);
      if (new_rank != rank) {
        rank = new_rank;
        printf("\n");
      }
    }
    if (verbose_output)
      printf("(%p)", n);
    for (i = 0; i < n->nKeys; i++) {
      if (verbose_output)
        printf("%p ", n->childrens[i]);
      printf("%d ", n->keys[i]);
    }
    if (!n->is_leaf)
      for (i = 0; i <= n->nKeys; i++)
        enQUEUE((node*)n->childrens[i]);
    if (verbose_output) {
      if (n->is_leaf)
        printf("%p ", n->childrens[order - 1]);
      else
        printf("%p ", n->childrens[n->nKeys]);
    }
    printf("| ");
  }
  printf("\n");
}


int main() {
	node *root;
	char instruction;

	root = NULL;

	char ch;
	int roll;
	do{

		cin>>ch;

		if(ch=='i'){
			int n;
			cin>>n;
			for(int i=0;i<n;i++){
				cin>>roll;
				root=insert(root,roll,0);
			}
			
		}else if(ch=='d'){
			cin>>roll;
			int searchnodeLevel=search(root,roll);
			if(searchnodeLevel==0){
				cout<<"No result found"<<endl;
			}else{
				
				root=delete_key(root,roll);
			}
		}else if(ch=='s'){
			cin>>roll;
			int searchnodeLevel=search(root,roll);
			if(searchnodeLevel==0){
				cout<<"No result found"<<endl;
			}else{
				cout<<searchnodeLevel<<endl;
			}


		}else if(ch=='p'){
			print_tree(root);
		}else if(ch=='t'){
			print_tree_struct(root);
		}


	}while(ch!='e');

}