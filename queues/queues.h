/*Autor:Joao Batanete
queue implementation in C. elements are stored as void pointers, to provide flexibility.

Operations:
-enqueue
-dequeue
-peek
(every operation is guaranteed to be O(1) ammortized)

Supports resizes when initial capacity is exceeded.
*/

#ifndef QUEUESBATA
#define QUEUESBATA

typedef struct queue_str* queueptr;

typedef struct queue_str {
	void** elements;
	unsigned front_index;
	unsigned back_index;
	unsigned n_elements;
	unsigned capacity;
} queue;

// creates a new queue and returns a pointer to it.
// returns NULL in case malloc fails.
queueptr queue_create(unsigned initial_capacity);

// frees the heap memory taken by the given queue
void queue_delete(queueptr queue);

// enqueues an element in the queue. if capacity is exceeded, it will perform a resize.
// returns -1 in case of memory error during a resize.
int queue_insert(queueptr queue, void* element);

// removes element at the front of the queue and returns it.
// if queue is empty, returns NULL instead
void* queue_remove(queueptr queue);

// returns element at the front of the queue without removing it.
// if queue is empty, returns NULL instead.
void* queue_peek(queueptr queue);

// duplicates capacity of queue. returns -1 if memory is exceeded.
void queue_resize(queueptr queue);

#endif