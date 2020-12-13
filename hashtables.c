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
unsigned long hash_function(unsigned int size, char* key){
	unsigned long res = 5381; //djb2
	//unsigned long res = 0; //others
    int c;

    while ((c = *key++))
		//res += c; //lose lose
		res = ((res << 5) + res) + c; /* hash * 33 + c (djb2)*/
		//res = c + (res << 6) + (res << 16) - res; //sdbm
	res=res%size;
	
	
	return res;
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

//returns a new hashtable with the desired maxsize.
//if there isn't enough memory, returns NULL
htptr create_hash_table(unsigned int size){
	//TODO testing with other functions
	htptr res;
	
	res=(htptr)malloc(sizeof(ht));
	
	//not enough memory
	if(res==NULL)
		return NULL;
	
	res->n_elements=0;
	res->size=size;
	res->keys=NULL;
	
	res->table=(ht_node**)calloc(size*sizeof(ht_node*));
	
	
	return res;
}

//prints the ht on screen.receives a pointer to a function to print the value fields.
//note that this function won't work correctly for HT's with values of different print functions.
void ht_print(htptr h,void(*print)(void*)){
	key_list* kl;
	int i;
	
	kl=h->keys;
	
	printf("{");
	for(i=0;i<h->n_elements;i++){
		printf("%s:",kl->key);
		
		print(kl->ht_node_ptr->value);
		
		if(i<h->n_elements-1)
			printf(",");
		kl=kl->next;
	}
	printf("}\n");
	
}

//deletes hashtable, freeing up the memory it took, along with all of it's elements(not including the value pointers)
//returns -1 on fail and 0 on success.
int ht_delete(htptr h){
	key_list* klptr,*next;
	ht_node* htnodeptr;
	int i;
	
	klptr=h->keys;
	
	for(i=0;i<h->n_elements;i++){
		htnodeptr=klptr->ht_node_ptr;
		
		//delete this key's node on the table
		free(htnodeptr);
		
		next=klptr->next;
		//delete the previous node on key list(the one we just used to access the node on the table).
		free(klptr);
		
		klptr=next;
		
	}
	
	free(h->table);
	free(h);
	return 0;
}

//returns the value associated with the given key on ht, or NULL if the key doesn't exist on it.
//not that if you have a key associated with the value NULL, it will still return NULL, so it's best
//not to do that.
void* ht_get(htptr h,char* k){
	unsigned long index;
	ht_node* aux;
	
	index=hash_function(h->size,k);
	
	aux=h->table[index];
	
	if(strcmp(aux->key,k)==0){
		return aux->value;
	}
	
	aux=aux->next;
	while(aux!=h->table[index]){
		if(strcmp(aux->key,k)==0){
			return aux->value;
		}
		else
			aux=aux->next;
	}
	
	//key doesn't exist on ht
	return NULL;
}

//inserts a new element on the hashtable with a given key and value(void pointer). 
//returns 1 if there were collisions during insertion and 0 if not.
//or -1 if an error ocurred.
int ht_insert(htptr h,char* k,void* v){
	//TODO test with other functions
	int res=0,index;
	ht_node** table;
	ht_node* aux,*auxnext;
	key_list *klptr,*auxkl;
	
	//key too big
	if(strlen(k)>=MAX_KEY_SIZE)
		return -1;
	
	index=hash_function(h->size,k);
	
	table=h->table;
	
	//no collisions
	if(table[index]==NULL){
		table[index]=(ht_node*) malloc(sizeof(ht_node));
		
		strcpy(table[index]->key,k);
		table[index]->value=v;
		table[index]->next=table[index];
		table[index]->previous=table[index];
		aux=table[index];
	}
	//index already set(collision or key already set)
	else{
		aux=table[index];
		res=1;
		
		//key already set. simply replace value and return.
		if(strcmp(aux->key,k)==0){
			table[index]->value=v;
			
			return 0;
		}
				
		aux=aux->next;
		//advance until end of the list of nodes on index
		while(aux!=table[index]){
			
			//key already set. simply replace value and return.
			if(strcmp(aux->key,k)==0){
				aux->next->value=v;
				return 0;
			}
			
			aux=aux->next;
		}
		
		auxnext=table[index]->next;
		table[index]->next=(ht_node*) malloc(sizeof(ht_node));
		
		strcpy(table[index]->next->key,k);
		table[index]->next->value=v;
		table[index]->next->previous=table[index];
		table[index]->next->next=auxnext;

		auxnext->previous=table[index]->next;
		
		aux=table[index]->next;
	}
	
	//insert key into keys list
	//list empty
	if(h->keys==NULL){
		h->keys=(key_list*)malloc(sizeof(key_list));
		strcpy(h->keys->key,k);
		
		h->keys->next=h->keys;
		h->keys->previous=h->keys;
	}
	//list not empty
	else{
		klptr=h->keys;
		
		h->keys=(key_list*)malloc(sizeof(key_list));
		strcpy(h->keys->key,k);
		
		auxkl=klptr->previous;
		klptr->previous=h->keys;
		auxkl->next=h->keys;
		h->keys->previous=auxkl;
		h->keys->next=klptr;
	}
	klptr=h->keys;
	
	aux->key_node_ptr=klptr;
	klptr->ht_node_ptr=aux;

	h->n_elements++;
	return res;
}

//deletes an element from the hashtable. 
//returns -1 if element with the given key does not exist on ht.
void* ht_remove(htptr h,char* k){
	void* res;
	unsigned long index;
	ht_node* aux;
	key_list *kl,*auxprev;
	
	index=hash_function(h->size,k);
	
	aux=h->table[index];
	
	//no element with given hash exists on ht.
	if(!aux)
		return NULL;
	
	//the element to delete is the first node.
	if(strcmp(aux->key,k)==0){
		res=aux->value;
		kl=aux->key_node_ptr;
		
		//only one node on index.
		if(aux->next==aux){
			h->table[index]=NULL;
			free(aux);	
		}
		else{
			h->table[index]=aux->next;
			h->table[index]->previous=aux->previous;
			free(aux);
		}
		
		//remove key from keys list
		if(h->n_elements==1)
			h->keys=NULL;
		else{
			auxprev=kl->previous;
			auxprev->next=kl->next;
			kl->next->previous=auxprev;
		}
		free(kl);
		
		h->n_elements--;
		return res;
	}
	
	aux=aux->next;
	while(aux!=h->table[index]){
		//key matches
		if(strcmp(aux->key,k)==0){
			res=aux->value;
			kl=aux->key_node_ptr;
			
			aux->previous->next=aux->next;
			aux->next->previous=aux->previous;
			free(aux);
			
			//remove key from keys list
			kl->previous->next=kl->next;
			kl->next->previous=kl->previous;
			free(kl);
			
			h->n_elements--;
			return res;
		}
		else
			aux=aux->next;
	}
	
	//key doesn't exist on ht
	return NULL;
}



