#ifndef PROD_CONS_H
#define PROD_CONS_H

#include <stdlib.h>
#include <assert.h>

typedef struct queue_
  unsigned *tasks;
  unsigned size, head, tail;
  unsigned const MAX;
} queue_t;

/**
 * Creates new queue
 * unsigned - queue max size
 */
queue_t *new_queue(unsigned);

/**
 * Removes from a queue
 * queue_t * - address of the queue
 */
unsigned pop(queue_t *);

/**
 * Insert into a queue
 * queue_t *  - address of the queue
 * unsigned   - element to insert
 */
void push(queue_t *, unsigned);

/*
 * Destroys a queue
 * queue_t * - address of the queue
 */
void queue_t destroy_queue(queue_t *);


#endif // PROD_CONS_H
