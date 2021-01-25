#include "queues.h"
#include <stdlib.h>


// functions included in .h

queueptr queue_create(unsigned max_elements) {
	queueptr queue = (queueptr)malloc(sizeof(struct queue_str));

	queue->elements = (void**)malloc(sizeof(void*) * max_elements);

	queue->front_index = 0;
	queue->back_index = 0;
	queue->max_elements = max_elements;
	queue->n_elements = 0;

	return queue;
}

void queue_delete(queueptr queue) {
	free(queue->elements);
	free(queue);
}

int queue_insert(queueptr queue, void* element) {
	if (queue->n_elements == queue->max_elements) {
		return -1;
	}

	queue->elements[queue->back_index] = element;
	queue->back_index = (queue->back_index + 1) % queue->max_elements;
	++queue->n_elements;
	return 0;
}

void* queue_remove(queueptr queue) {
	if (queue->n_elements == 0) {
		return NULL;
	}
	int front_index = queue->front_index;

	void* result = queue->elements[front_index];
	queue->front_index = (front_index + 1) % queue->max_elements;
	--queue->n_elements;

	return result;
}


void* queue_peek(queueptr queue) {
	if (queue->n_elements == 0) {
		return NULL;
	}

	return queue->elements[queue->front_index];
}