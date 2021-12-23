#include "tests.h"
#include "../hashtables/hashtables.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

static char test_key[12];

static char* set_test_key(unsigned long n) {
	sprintf(test_key, "%ld", n);
	return test_key;
}

static void insert_one_and_remove() {
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

	printf("Hashtables: insert_one_and_remove passed\n");
}

static void many_inserts_and_removes() {
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

	printf("Hash tables: many_inserts_and_removes passed\n");
}

static void resizes() {
	unsigned long i;
	htptr ht = ht_create(100);
	assert(ht != NULL);
	assert(ht->n_elements == 0);
	void *value;

	for (i = 1; i <= HASHTABLE_LOAD_FACTOR * 100; ++i) {
		ht_insert(ht, set_test_key(i), (void *)i);
		assert(ht->n_elements == i);
		assert(ht->size == 100);
	}

	for (unsigned long j = 1; j < i; ++j) {
		value = ht_get(ht, set_test_key(j));
		assert(value == (void *)j);
	}

	// resize here
	ht_insert(ht, set_test_key(i), (void *)i);

	assert(ht->n_elements == i);
	assert(ht->size == 200);

	for (unsigned long j = 1; j < i; ++j) {
		value = ht_get(ht, set_test_key(j));
		assert(value == (void *)j);
	}

	for (i = i + 1; i <= HASHTABLE_LOAD_FACTOR * 200; ++i) {
		ht_insert(ht, set_test_key(i), (void *)i);
		assert(ht->n_elements == i);
		assert(ht->size == 200);
	}

	for (unsigned long j = 1; j < i; ++j) {
		value = ht_get(ht, set_test_key(j));
		assert(value == (void *)j);
	}

	// resize here
	ht_insert(ht, set_test_key(i), (void *)i);

	assert(ht->n_elements == i);
	assert(ht->size == 400);

	for (unsigned long j = 1; j <= i; ++j) {
		value = ht_get(ht, set_test_key(j));
		assert(value == (void *)j);
	}

	ht_delete(ht);

	printf("Hashtables: resizes passed\n");
}

void hashtable_tests() {
	insert_one_and_remove();
	many_inserts_and_removes();
	resizes();
}