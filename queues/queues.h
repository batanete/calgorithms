/*Autor:Joao Batanete
queue implementation in C. elements are stored as void pointers, to provide flexibility.

Operations:
-enqueue
-dequeue
-peek
(every operation is guaranteed to be O(1))

Note: does not support extending the queue once created.
*/

#ifndef QUEUESBATA
#define QUEUESBATA

typedef struct queue_str* queueptr;

typedef struct queue_str {
	void** elements;
	unsigned front_index;
	unsigned back_index;
	unsigned n_elements;
	unsigned max_elements;
} queue;

// creates a new queue and returns a pointer to it
queueptr queue_create(unsigned max_elements);

// frees the heap memory taken by the given queue
void queue_delete(queueptr queue);

// enqueues an element in the queue. returns -1 if the
// queue is full
int queue_insert(queueptr queue, void* element);

// removes element at the front of the queue and returns it.
// if queue is empty, returns NULL instead
void* queue_remove(queueptr queue);

// returns element at the front of the queue without removing it.
// if queue is empty, returns NULL instead.
void* queue_peek(queueptr queue);

#endif