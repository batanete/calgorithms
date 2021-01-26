#include "tries.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// auxiliary functions not exported in .h

static unsigned get_index(char c) {
	// ensure we do not use a negative array position...
	return c + 128;
}

static trieptr get_or_create_child(trieptr node, char c) {
	unsigned index = get_index(c);
	trieptr child = node->children[index];

	if (!child) {
		child = trie_create();
		node->children[index] = child;
		node->children_list[node->n_children] = c;
		++node->n_children;
	}

	return child;
}


// functions included in .h

trieptr trie_create() {
	// using calloc, as we do want the array to contain NULL entries,
	// and root to not be a string ending(we do not contain the empty string)
	return (trieptr)calloc(1, sizeof(trie_node));
}

void trie_delete(trieptr trie) {
	trieptr aux;
	// TODO: use a BFS traversal using a queue to prevent stack overflows in case of very large keys
	// (the maximum recursion depth will be the size of the largest entry present)
	for (int i = 0; i < 256; ++i) {
		aux = trie->children[i];
		if (aux) {
			trie_delete(aux);
		}
	}
	free(trie);
}

int trie_insert(trieptr trie, char* str) {
	unsigned size = strlen(str);
	if (size > trie->max_entry_size) {
		trie->max_entry_size = size;
	}

	trieptr current = trie;
	// if the string is empty, we consider the root to also be a string ending.
	// this way searches for the empty string will return a proper result.
	while (*str) {
		current = get_or_create_child(current, *str);
		if (current == NULL) {
			// Out of memory!!!
			return -1;
		}
		++str;
	}

	current->is_end = 1;
	return 0;
}

char* trie_search_prefix(trieptr trie, char* str) {
	// if the empty string is present, return it regardless of input
	if (trie->is_end) {
		return (char*)calloc(1, 1);
	}

	// if str is empty, and the empty string is not present, return NULL
	if (!*str) {
		return NULL;
	}

	char *buffer = (char*)malloc(trie->max_entry_size + 1);
	unsigned size = 0;

	while (*str) {
		char c = *str;

		trie = trie->children[get_index(c)];
		if (!trie) {
			return NULL;
		}
		buffer[size] = c;

		if (trie->is_end) {
			++size;
			char* result = (char*)malloc(size + 1);
			memcpy(result, buffer, size);
			result[size] = '\0';
			free(buffer);
			return result;
		}

		++str;
		++size;
	}
	free(buffer);
	return NULL;
}

char* trie_search_by_prefix(trieptr trie, char* prefix) {
	trieptr current_node_ptr = trie;
	unsigned index;
	unsigned max_size = trie->max_entry_size;

	while (*prefix) {
		index = get_index(*prefix);
		current_node_ptr = current_node_ptr->children[index];
		if (!current_node_ptr) {
			return 0;
		}
		++prefix;
	}
	char *buffer = (char*)malloc(max_size + 1);
	strcpy(buffer, prefix);
	unsigned buffer_size = strlen(prefix);

	// just traverse remaining nodes until we find a terminal one
	while (!current_node_ptr->is_end) {
		char c = current_node_ptr->children_list[0];
		index = get_index(c);
		current_node_ptr = current_node_ptr->children[index];
		buffer[buffer_size] = c;
		++buffer_size;
	}
	buffer[buffer_size] = '\0';

	char* result = (char*)malloc(strlen(buffer) + 1);
	strcpy(result, buffer);
	free(buffer);
	return result;
}