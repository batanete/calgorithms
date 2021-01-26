#include "queues.h"
#include <stdlib.h>
#include <string.h>

// functions included in .h

queueptr queue_create(unsigned initial_capacity) {
	queueptr queue = (queueptr)malloc(sizeof(struct queue_str));

	if (queue == NULL) {
		return NULL;
	}

	queue->elements = (void**)malloc(sizeof(void*) * initial_capacity);

	if (queue ->elements == NULL) {
		free(queue);
		return NULL;
	}

	queue->front_index = 0;
	queue->back_index = 0;
	queue->capacity = initial_capacity;
	queue->n_elements = 0;

	return queue;
}

void queue_delete(queueptr queue) {
	free(queue->elements);
	free(queue);
}

int queue_insert(queueptr queue, void* element) {
	if (queue->n_elements == queue->capacity) {
		queue_resize(queue);
	}

	queue->elements[queue->back_index] = element;
	queue->back_index = (queue->back_index + 1) % queue->capacity;
	++queue->n_elements;
	return 0;
}

void* queue_remove(queueptr queue) {
	if (queue->n_elements == 0) {
		return NULL;
	}
	int front_index = queue->front_index;

	void* result = queue->elements[front_index];
	queue->front_index = (front_index + 1) % queue->capacity;
	--queue->n_elements;

	return result;
}


void* queue_peek(queueptr queue) {
	return queue->n_elements == 0
		? NULL
		: queue->elements[queue->front_index];
}

void queue_resize(queueptr queue) {
	unsigned new_capacity = queue->capacity * 2;
	void** elements = queue->elements;
	queue->elements = (void**)malloc(sizeof(void*) * new_capacity);
	
	void** front = elements + queue->front_index;
	void** array_end = elements + queue->capacity;
	unsigned elements_in_front = array_end - front;
	
	// copy elements from front until array end, and then from array start until front
	// note that memcpy is faster than copying elements one by one
	memcpy(queue->elements, front, elements_in_front * sizeof(void*));
	memcpy(queue->elements + elements_in_front, elements, (front - elements) * sizeof(void*));

	queue->front_index = 0;
	queue->back_index = queue->n_elements;
	queue->capacity = new_capacity;
	free(elements);
}