#ifndef __QUEUE__H__
#define __QUEUE__H__
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * 1. qreate queue
 * 2. destroy queue
 * 3. enqueue
 * 4. dequeue
 */
#ifndef __N__
#define __N__
typedef struct Node
{
    struct Node *next;
    void *object;
} Node, *p_node;
#endif

#ifndef __Q__
#define __Q__
typedef struct queue
{
    p_node root;
    p_node tail;
    int id;
    pthread_mutex_t _lock;
    pthread_cond_t _cond ;
    int size;
} queue, *p_queue;
#endif

#ifndef __VALUE__
#define __VALUE__
typedef struct value
{
    int sock;
    char str[1024];
} value, *p_value;
#endif

/**
 * @brief create new queue
 * and initiallize cond,mutex to null
 * @return p_queue
 */
p_queue createQ();
/**
 * @brief loop through the queue
 * free all the nodes
 * @param q : given queue to destroy
 */
void destroyQ(p_queue);
/**
 * @brief add given element to the queue
 * check if the root is NULL, then just create new node that would
 * be the head and the tail, else add to the tail
 * @param object
 * @param q
 */
void* enQ(void *object, p_queue q);
/**
 * @brief get the first added node
 * @param q
 * @return void*
 */
void *deQ(p_queue q);
/**
 * @brief check if the queue is empty
 *
 * @param q
 * @return 0 if empty, 1 if not
 */
int isEmpty(p_queue q);

#endif //!__QUEUE__H__