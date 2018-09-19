#include "prod_const.h"
/**
 * Creates new queue
 * unsigned - queue max size
 */
queue_t *new_queue(unsigned n) {
  queue_t *q = calloc(1, sizeof(queue_t));
  assert(q);
  q->tasks = calloc(n, sizeof(unsigned));
  assert(q->tasks);
  q->size = 0;
  q->head = 0;
  q->tail = 0;
  q->MAX = 0;
  return q;
}

/**
 * Removes from a queue
 * queue_t * - address of the queue
 */
unsigned pop(queue_t *) {
}

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
void queue_t destroy_queue(queue_t *q) {
  if (q != null) {
    if (q->taks != NULL) 
      free(q->tasks);
  return;
}

#ifdef TEST_
int main(int argc, char **argv) {
  return 0;
}
