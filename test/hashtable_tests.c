#include "../hashtables/hashtables.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


void insert_one_and_remove() {
	htptr ht = ht_create(100);
	assert(ht != NULL);
	assert(ht->n_elements == 0);

	char key[] = "stuff";
	int val = 100;

	ht_insert(ht, key, &val);
	assert(ht->n_elements == 1);

	val = *((int*)ht_get(ht, key));
	assert(ht->n_elements == 1);
	assert(val == 100);

	val = *((int*)ht_remove(ht, key));
	assert(ht->n_elements == 0);
	assert(val == 100);

	ht_delete(ht);

	printf("insert_one_and_remove passed\n");
}


void many_inserts_and_removes() {
	char key1[] = "stuff1", key2[] = "stuff2", key3[] = "stuff3";
	int val1 = 101, val2 = 102, val3 = 103, new_val1 = 111, aux;

	htptr ht = ht_create(100);
	assert(ht != NULL);
	assert(ht->n_elements == 0);

	ht_insert(ht, key1, &val1);
	assert(ht->n_elements == 1);

	ht_insert(ht, key2, &val2);
	assert(ht->n_elements == 2);

	aux = *(int*)ht_get(ht, key1);
	assert(aux == val1);

	aux = *(int*)ht_get(ht, key2);
	assert(aux == val2);

	aux = *(int*)ht_remove(ht, key2);
	assert(ht->n_elements == 1);
	assert(aux == val2);

	// override old value
	ht_insert(ht, key1, &new_val1);
	aux = *(int*)ht_get(ht, key1);
	assert(aux == new_val1);
	assert(ht->n_elements == 1);

	ht_insert(ht, key3, &val3);
	aux = *(int*)ht_get(ht, key3);
	assert(aux == val3);
	assert(ht->n_elements == 2);

	ht_delete(ht);

	printf("many_inserts_and_removes passed\n");
}

int main() {

	insert_one_and_remove();
	many_inserts_and_removes();

	return 0;
}