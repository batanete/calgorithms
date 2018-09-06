

/*Autor:Joao Batanete
Hashtable implementation in C(works for values any data type,keys are strings).

*/

#ifndef HASHTABLESBATA
#define HASHTABLESBATA

#define MAX_KEY_SIZE 30

//structure where each key/value pair is stored.
//since it's possible to have more than one node on a table index, we need a pointer
//to the possible next and previous nodes(also for easier deletions).
typedef struct ht_node_str{
	char key[MAX_KEY_SIZE+1];
	void* value;
	struct ht_node_str* next;
	struct ht_node_str* previous;
	
	//reference to this key's node on the table's key list.
	//helps us delete it faster when we do a deletion.
	struct key_list_str* key_node_ptr;
	
} ht_node;


//structure where we will store the keys list for the hash table, so we can traverse it more easily.
typedef struct key_list_str{
	char key[MAX_KEY_SIZE+1];
	
	struct ht_node_str* ht_node_ptr;
	struct key_list_str* next;
	struct key_list_str* previous;
}key_list;

//structure used for the header of the ht.
typedef struct{
	
	ht_node** table;
	
	key_list* keys;
	
	unsigned int n_elements;
	unsigned int size;
	
}ht;

//define htptr as a pointer to a ht for simplicity's sake
typedef ht* htptr;

//returns a new hashtable with the desired size.
//if there isn't enough memory, returns NULL
htptr create_hash_table(unsigned int);

//deletes hashtable, freeing up the memory it took, along with all of it's elements(not including the value pointers)
int ht_delete(htptr);

//prints the ht on screen.receives a pointer to a function to print the value fields.
//note that this function won't work correctly for HT's with values of different print functions.
void ht_print(htptr,void(*)(void*));

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
