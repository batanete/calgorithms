/*Autor:Joao Batanete
String(char[]) Trie implementation in C.

Operations:
-insert string entry
-search for entries which are a prefix of a given string(takes at the most O(m) time, where m is the length of the largest entry in the trie)
-search for entries which starts with a given string(takes at the most O(n) time, where n is the length of the string)
-search for entries which contain a given string anywhere(takes at the most mlogn where m is the length of the largest entry, and n is the string length)

*/

#ifndef TRIESBATA
#define TRIESBATA

// define trieptr as a pointer to a trie for simplicity's sake
typedef struct trie_node_str* trieptr;

// structure where trie node is stored
typedef struct trie_node_str {
	 trieptr children[256];
	 // used so we can traverse the list of children more easily(useful in search by prefix)
	 char children_list[256];
	 unsigned n_children;
	 // TODO: this only needs to be present on root node
	 unsigned max_entry_size;

	 unsigned is_end; 
} trie_node;

// creates an empty trie and returns a pointer to the root
trieptr trie_create();

// frees up memory taken by the given trie
void trie_delete(trieptr trie);

// inserts a string into the trie
// returns -1 if there is not enough memory
int trie_insert(trieptr trie, char* str);

// searches for a prefix to the given string in the trie
// returns NULL if not found
char* trie_search_prefix(trieptr trie, char* str);

// searches for an entry to which the given string is a prefix
// returns NULL if not found
char* trie_search_by_prefix(trieptr trie, char* prefix);

// TODO: equivalent functions which return ALL entries, rather than one

#endif //TRIESBATA