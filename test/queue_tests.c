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
	assert(queue->max_elements == 100);
	assert(queue_peek(queue) == NULL);
	assert(queue_remove(queue) == NULL);

	assert(queue_insert(queue, str) != -1);
	assert(queue->n_elements == 1);
	assert(queue->max_elements == 100);
	assert(queue_peek(queue) == str);

	assert(queue_remove(queue) == str);
	assert(queue->n_elements == 0);
	assert(queue->max_elements == 100);
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
	assert(queue->max_elements == 100);
	assert(queue_peek(queue) == NULL);
	assert(queue_remove(queue) == NULL);

	queue_insert(queue, str1);
	assert(queue->n_elements == 1);
	assert(queue->max_elements == 100);
	assert(queue_peek(queue) == str1);

	queue_insert(queue, str2);
	assert(queue->n_elements == 2);
	assert(queue->max_elements == 100);
	assert(queue_peek(queue) == str1);

	assert(queue_remove(queue) == str1);
	assert(queue->n_elements == 1);
	assert(queue->max_elements == 100);
	assert(queue_peek(queue) == str2);

	queue_insert(queue, str1);
	assert(queue->n_elements == 2);
	assert(queue->max_elements == 100);
	assert(queue_peek(queue) == str2);

	assert(queue_remove(queue) == str2);
	assert(queue->n_elements == 1);
	assert(queue->max_elements == 100);
	assert(queue_peek(queue) == str1);

	assert(queue_remove(queue) == str1);
	assert(queue->n_elements == 0);
	assert(queue->max_elements == 100);
	assert(queue_peek(queue) == NULL);

	queue_delete(queue);

	printf("Queues: many_inserts_peeks_and_removes passed\n");
}

static void with_rotation_involved() {
	char str1[] = "str1", str2[] = "str2", str3[] = "str3", str4[] = "str4";

	queueptr queue = queue_create(3);
	assert(queue->n_elements == 0);
	assert(queue->max_elements == 3);
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

	printf("Queues: with_rotation_involved passed\n");
}

void queue_tests() {
	insert_one_and_remove();
	many_inserts_peeks_and_removes();
	with_rotation_involved();
}