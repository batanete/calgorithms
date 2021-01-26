#include "tests.h"
#include "../queues/queues.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


static void insert_one_and_remove() {
	char str[] = "str";

	queueptr queue = queue_create(100);

	assert(queue != NULL);
	assert(queue->n_elements == 0);
	assert(queue->capacity == 100);
	assert(queue_peek(queue) == NULL);
	assert(queue_remove(queue) == NULL);

	assert(queue_insert(queue, str) != -1);
	assert(queue->n_elements == 1);
	assert(queue->capacity == 100);
	assert(queue_peek(queue) == str);

	assert(queue_remove(queue) == str);
	assert(queue->n_elements == 0);
	assert(queue->capacity == 100);
	assert(queue_peek(queue) == NULL);
	assert(queue_remove(queue) == NULL);

	queue_delete(queue);

	printf("Queues: insert_one_and_remove passed\n");
}

static void many_inserts_peeks_and_removes() {
	char str1[] = "str";
	char str2[] = "str2";

	queueptr queue = queue_create(100);
	assert(queue->n_elements == 0);
	assert(queue->capacity == 100);
	assert(queue_peek(queue) == NULL);
	assert(queue_remove(queue) == NULL);

	queue_insert(queue, str1);
	assert(queue->n_elements == 1);
	assert(queue->capacity == 100);
	assert(queue_peek(queue) == str1);

	queue_insert(queue, str2);
	assert(queue->n_elements == 2);
	assert(queue->capacity == 100);
	assert(queue_peek(queue) == str1);

	assert(queue_remove(queue) == str1);
	assert(queue->n_elements == 1);
	assert(queue->capacity == 100);
	assert(queue_peek(queue) == str2);

	queue_insert(queue, str1);
	assert(queue->n_elements == 2);
	assert(queue->capacity == 100);
	assert(queue_peek(queue) == str2);

	assert(queue_remove(queue) == str2);
	assert(queue->n_elements == 1);
	assert(queue->capacity == 100);
	assert(queue_peek(queue) == str1);

	assert(queue_remove(queue) == str1);
	assert(queue->n_elements == 0);
	assert(queue->capacity == 100);
	assert(queue_peek(queue) == NULL);

	queue_delete(queue);

	printf("Queues: many_inserts_peeks_and_removes passed\n");
}

static void with_rotation() {
	char str1[] = "str1", str2[] = "str2", str3[] = "str3", str4[] = "str4";

	queueptr queue = queue_create(3);
	assert(queue->n_elements == 0);
	assert(queue->capacity == 3);
	assert(queue_peek(queue) == NULL);
	assert(queue_remove(queue) == NULL);

	queue_insert(queue, str1);
	queue_insert(queue, str2);

	assert(queue->n_elements == 2);
	assert(queue_remove(queue) == str1);
	assert(queue->n_elements == 1);
	assert(queue_peek(queue) == str2);

	queue_insert(queue, str3);
	queue_insert(queue, str4);

	assert(queue->n_elements == 3);
	assert(queue_peek(queue) == str2);
	assert(queue_remove(queue) == str2);

	assert(queue->n_elements == 2);
	assert(queue_peek(queue) == str3);
	assert(queue_remove(queue) == str3);

	assert(queue->n_elements == 1);
	assert(queue_peek(queue) == str4);
	assert(queue_remove(queue) == str4);

	assert(queue->n_elements == 0);
	assert(queue_peek(queue) == NULL);
	assert(queue_remove(queue) == NULL);

	queue_delete(queue);

	printf("Queues: with_rotation passed\n");
}

static void with_resizes() {
	int ints[30];
	int i;

	for (i = 0; i < 30; ++i) {
		ints[i] = i;
	}

	queueptr queue = queue_create(10);
	assert(queue_peek(queue) == NULL);
	assert(queue->capacity == 10);
	assert(queue->n_elements == 0);

	for (i = 0; i < 10; ++i) {
		assert(queue_insert(queue, ints + i) != -1);
		assert(*(int*)queue_peek(queue) == 0);
		assert(queue->capacity == 10);
		assert(queue->n_elements == i + 1);
	}

	for (i = 10; i < 20; ++i) {
		assert(queue_insert(queue, ints + i) != -1);
		assert(*(int*)queue_peek(queue) == 0);
		assert(queue->capacity == 20);
		assert(queue->n_elements == i + 1);
	}

	// tests involving rotations below

	assert(*(int*)queue_remove(queue) == 0);
	assert(*(int*)queue_peek(queue) == 1);
	assert(queue->n_elements == 19);
	assert(queue->capacity == 20);

	assert(*(int*)queue_remove(queue) == 1);
	assert(*(int*)queue_peek(queue) == 2);
	assert(queue->n_elements == 18);
	assert(queue->capacity == 20);

	assert(*(int*)queue_remove(queue) == 2);
	assert(*(int*)queue_peek(queue) == 3);
	assert(queue->n_elements == 17);
	assert(queue->capacity == 20);

	assert(queue_insert(queue, ints + 20) != -1);
	assert(*(int*)queue_peek(queue) == 3);
	assert(queue->n_elements == 18);
	assert(queue->capacity == 20);
	// if this fails, there's something wrong with rotations
	assert(*(int*)queue->elements[0] == 20);

	assert(queue_insert(queue, ints + 21) != -1);
	assert(*(int*)queue_peek(queue) == 3);
	assert(queue->n_elements == 19);
	assert(queue->capacity == 20);
	// if this fails, there's something wrong with rotations
	assert(*(int*)queue->elements[1] == 21);

	assert(queue_insert(queue, ints + 22) != -1);
	assert(*(int*)queue_peek(queue) == 3);
	assert(queue->n_elements == 20);
	assert(queue->capacity == 20);
	// if this fails, there's something wrong with rotations
	assert(*(int*)queue->elements[2] == 22);

	assert(queue_insert(queue, ints + 23) != -1);
	printf("actual:%d\n", *(int*)queue_peek(queue));
	assert(*(int*)queue_peek(queue) == 3);
	assert(queue->n_elements == 21);
	assert(queue->capacity == 40);
	// if this fails, there's something wrong with resize, when a rotation was done before
	assert(*(int*)queue->elements[17] == 20);

	assert(queue_insert(queue, ints + 24) != -1);
	assert(*(int*)queue_peek(queue) == 3);
	assert(queue->n_elements == 22);
	assert(queue->capacity == 40);

	for (i = 0; i < 22; ++i) {
		int *aux = (int*)queue->elements[i];
		assert(*aux == i + 3);
		++aux;
	}

	unsigned expected_elements = 22;
	for (i = 3; i < 25; ++i) {
		assert(queue->n_elements == expected_elements);
		assert(*(int*)queue_peek(queue) == i);
		assert(*(int*)queue_remove(queue) == i);
		assert(queue->capacity == 40);
		--expected_elements;
	}

	queue_delete(queue);
	printf("Queues: with_resizes passed\n");
}

void queue_tests() {
	insert_one_and_remove();
	many_inserts_peeks_and_removes();
	with_rotation();
	with_resizes();
}