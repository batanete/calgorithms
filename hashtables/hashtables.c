#include "hashtables.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
 * 
 * 
 * functions not included in .h file(auxiliary functions)
 * 
 * 
 * 
 * 
 */

//returns the index for the given key and table size
static unsigned long hash_function(unsigned int size, char* key) {
	unsigned long res = 5381; //djb2
	//unsigned long res = 0; //others
    int c;

    while ((c = *key++))
		//res += c; //lose lose
		res = ((res << 5) + res) + c; /* hash * 33 + c (djb2)*/
		//res = c + (res << 6) + (res << 16) - res; //sdbm
	res = res % size;
	
	
	return res;
}

static void node_init(ht_node* node_ptr, char* key, char* value) {
	strcpy(node_ptr->key, key);
	node_ptr->value = value;
	node_ptr->next = NULL;
}

static int resize(htptr ht) {
	htptr copy = ht_create(ht->size * 2);

	// OOM
	if (copy == NULL) return -1;

	unsigned int inserted = 0;
	ht_node *curr = ht->table;

	while (inserted < ht->n_elements) {
		if (curr->value) {
			if (ht_insert(copy, curr->key, curr->value) == -1) {
				ht_delete(copy);
				return -1;
			}
			++inserted;
		}

		// insert every other entry at this node(there may be more than one due to collisions)
		// also delete the extra nodes from the old structure
		ht_node *node_curr = curr->next;
		ht_node *node_prev;
		while (node_curr) {
			if (ht_insert(copy, node_curr->key, node_curr->value) == -1) {
				ht_delete(copy);
				return -1;
			}

			node_prev = node_curr;
			node_curr = node_curr->next;

			free(node_prev);
			++inserted;
		}
		
		++curr;
	}

	ht->size = copy->size;
	ht->table = copy->table;
	free(copy);

	return 0;
}

/*
 * 
 * 
 * functions included in .h file
 * 
 * 
 * 
 * 
 */

htptr ht_create(unsigned int size) {
	htptr res;
	
	res = (htptr)malloc(sizeof(ht));
	
	//not enough memory
	if(res == NULL)
		return NULL;
	

	res->n_elements = 0;
	res->size = size;
	
	res->table = (ht_node*)calloc(size, sizeof(ht_node));
	return res;
}

int ht_delete(htptr ht) {
	ht_node* nodeptr;
	int i;
	nodeptr = ht->table;
	
	for (i = 0; i < ht->size; ++i) {
		ht_node* curr = nodeptr->next;
		// free each node on this bucket
		while (curr) {
			ht_node* prev = curr;
			curr = prev->next;
			free(prev);
		}

		++nodeptr;
	}
	
	free(ht->table);
	free(ht);
	return 0;
}

void* ht_get(htptr h, char* k) {
	unsigned long index;
	ht_node* aux;
	
	index = hash_function(h->size,k);
	
	aux = &h->table[index];
	
	while (aux) {
		if (strcmp(aux->key, k) == 0){
			return aux->value;
		}

		aux = aux->next;
	}
	
	// key doesn't exist on ht
	return NULL;
}

int ht_insert(htptr ht, char* key, void* value) {
	int res = 0, index;
	ht_node* node;
	
	// key too big
	if (strlen(key) >= HASHTABLE_MAX_KEY_SIZE) {
		return -1;
	}

	if (ht->size * HASHTABLE_LOAD_FACTOR < ht->n_elements + 1) {
		if (resize(ht) == -1) {
			return -1;
		}
	}

	index = hash_function(ht->size, key);

	node = &ht->table[index];
	
	// no collision(we assume key isn't set if value is NULL)
	if(node == NULL) {
		node_init(node, key, value);
		++ht->n_elements;
		return 0;
	}

	// collision or key already set
	while (node->next) {
		// replace value if key already set
		if (strcmp(key, node->key) == 0) {
			node->value = value;
			return 0;
		}
		node = node->next;
	}

	// replace value if key already set
	if (strcmp(key, node->key) == 0) {
		node->value = value;
		return 0;
	}
	node->next = (ht_node*)malloc(sizeof(ht_node));
	node_init(node->next, key, value);
	++ht->n_elements;

	return res;
}

void* ht_remove(htptr ht,char* key) {
	unsigned long index = hash_function(ht->size, key);
	
	ht_node* node = &ht->table[index];
	
	// the element to delete is the first node in the bucket
	// in this case, we simply make the value NULL. this is more efficient
	// than traversing the entire list and "pulling" elements back, and makes the next insertion
	// on this bucket "collision free" since the element can be inserted on the first node.
	if (strcmp(node->key, key) == 0) {
		void* res = node->value;
		node->value = NULL;
		--ht->n_elements;
		return res;
	}

	while (node->next) {
		ht_node* previous = node;
		node = node->next;
		
		if (strcmp(node->key, key) == 0) {
			void* res = node->value;
			previous->next = node->next;
			--ht->n_elements;
			free(node);
			return res;
		}
	}
	
	// key doesn't exist on ht
	return NULL;
}

char** ht_get_all_keys(htptr ht) {
	char **result = (char**)malloc(sizeof(char*) * ht->n_elements);
	ht_node* nodeptr = ht->table;
	int index = 0;

	while (index < ht->n_elements) {
		// get each key on this bucket
		if (nodeptr->value != NULL) {
			result[index] = nodeptr->key;
			++index;
		}

		ht_node* curr = nodeptr->next;
		while (curr) {
			result[index] = curr->key;
			++index;

			ht_node* prev = curr;
			curr = prev->next;
		}

		++nodeptr;
	}
	
	return result;
}