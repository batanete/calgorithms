#include "tests.h"
#include "../tries/tries.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>


static void search_prefix() {
	trieptr trie = trie_create();
	assert(trie != NULL);
	assert(trie_insert(trie, "911") != -1);
	assert(trie_insert(trie, "12") != -1);
	// repeated on purpose
	assert(trie_insert(trie, "12") != -1);

	assert(trie_insert(trie, "32") != -1);
	assert(trie_insert(trie, "4") != -1);
	assert(trie_insert(trie, "53123") != -1);
	assert(trie_insert(trie, "888") != -1);

	char* result;

	result = trie_search_prefix(trie, "122222");
	assert(strcmp(result, "12") == 0);
	free(result);

	result = trie_search_prefix(trie, "4");
	assert(strcmp(result, "4") == 0);
	free(result);

	result = trie_search_prefix(trie, "41");
	assert(strcmp(result, "4") == 0);
	free(result);

	result = trie_search_prefix(trie, "911");
	assert(strcmp(result, "911") == 0);
	free(result);

	result = trie_search_prefix(trie, "9110");
	assert(strcmp(result, "911") == 0);
	free(result);

	result = trie_search_prefix(trie, "7777");
	assert(result == NULL);
	free(result);

	result = trie_search_prefix(trie, "");
	assert(result == NULL);

	// insert empty string, should now be returned for everything
	assert(trie_insert(trie, "") != -1);

	result = trie_search_prefix(trie, "911");
	assert(strcmp(result, "") == 0);
	free(result);

	result = trie_search_prefix(trie, "9110");
	assert(strcmp(result, "") == 0);
	free(result);

	result = trie_search_prefix(trie, "7777");
	assert(strcmp(result, "") == 0);
	free(result);

	result = trie_search_prefix(trie, "");
	assert(strcmp(result, "") == 0);
	free(result);

	trie_delete(trie);

	printf("Tries: search_prefix passed\n");
}


static void search_by_prefix() {
	trieptr trie = trie_create();
	assert(trie != NULL);
	
	assert(trie_insert(trie, "12345") != -1);
	assert(trie_insert(trie, "12345") != -1);
	assert(trie_insert(trie, "01234") != -1);
	assert(trie_insert(trie, "00123") != -1);
	assert(trie_insert(trie, "00000") != -1);

	char* result;

	result = trie_search_by_prefix(trie, "");
	assert(strcmp(result, "00000"));
	free(result);

	result = trie_search_by_prefix(trie, "0");
	assert(strcmp(result, "00000"));
	free(result);

	result = trie_search_by_prefix(trie, "00");
	assert(strcmp(result, "00000"));
	free(result);

	result = trie_search_by_prefix(trie, "000");
	assert(strcmp(result, "00000"));
	free(result);

	result = trie_search_by_prefix(trie, "0000");
	assert(strcmp(result, "00000"));
	free(result);

	result = trie_search_by_prefix(trie, "00000");
	assert(strcmp(result, "00000"));
	free(result);

	result = trie_search_by_prefix(trie, "000000");
	assert(result == NULL);

	result = trie_search_by_prefix(trie, "01");
	assert(strcmp(result, "012345"));
	free(result);

	result = trie_search_by_prefix(trie, "001");
	assert(strcmp(result, "00123"));
	free(result);

	result = trie_search_by_prefix(trie, "000001");
	assert(result == NULL);

	trie_delete(trie);
	printf("Tries: search_by_prefix passed\n");
}

void trie_tests() {
	search_prefix();
	search_by_prefix();
}