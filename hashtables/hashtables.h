

/*Autor:Joao Batanete
Hashtable implementation in C(works for values any data type,keys are strings).

*/

#ifndef HASHTABLESBATA
#define HASHTABLESBATA

#define MAX_KEY_SIZE 30

// structure where each key/value pair is stored.
// since it's possible to have more than one node on a table index(in case of collisions),
// we need to store them as a linked list, hence the next pointer
typedef struct ht_node_str{
	char key[MAX_KEY_SIZE+1];
	void* value;
	struct ht_node_str* next;
	
} ht_node;


//structure used for the header of the ht.
typedef struct{
	
	ht_node* table;
	
	unsigned int n_elements;
	unsigned int size;
	
}ht;

//define htptr as a pointer to a ht for simplicity's sake
typedef ht* htptr;

//returns a new hashtable with the desired size.
//if there isn't enough memory, returns NULL
htptr ht_create(unsigned int);

//deletes hashtable, freeing up the memory it took, along with all of it's elements(not including the value pointers)
int ht_delete(htptr);

//inserts a new element on the hashtable with a given key and value(void pointer). 
//returns 1 if there were collisions during insertion and 0 if not.
//or -1 if an error ocurred.
int ht_insert(htptr,char*,void*);

//deletes an element from the hashtable. returns the value of the element removed or
//NULL if element with the given key does not exist on ht.
//note that if you have a key associated with the value NULL, it will still return NULL, so it's best
//not to do that.
void* ht_remove(htptr,char*);

//returns the value associated with the given key on ht, or NULL if the key doesn't exist on it.
//note that if you have a key associated with the value NULL, it will still return NULL, so it's best
//not to do that.
void* ht_get(htptr,char*);

#endif //HASHTABLESBATA
