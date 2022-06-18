#include "queue.hpp"
#include "../color.hpp"
/**
 * Implementation of Q1,Q2,Q3
 */

/**
 * initializing mutex and condition variable
 */

p_queue createQ()
{

    p_queue new_q = (p_queue)malloc(sizeof(queue));
    new_q->root = NULL;
    new_q->tail = NULL;
    if (pthread_mutex_init(&new_q->_lock, NULL) != 0)
    {
        printf("\n mutex init has failed\n");
        return 0;
    }
     if (pthread_cond_init(&new_q->_cond, NULL) != 0)
    {
        printf("\n cond init has failed\n");
        return 0;
    }
    return new_q;
}
void destroyQ(p_queue q)
{
    if (q->root == NULL)
    {
        printf("Queue already destroyed\n");
        return;
    }

    while (q->root != NULL)
    {
        p_node curr = q->root;
        q->root = q->root->next;
        free(curr);
    }
    q->size = 0;
}
void* enQ(void *object, p_queue q)
{
    pthread_mutex_lock(&q->_lock);
    p_node new_n = (p_node)malloc(sizeof(Node));
    if (new_n == NULL)
    {
        printf("malloc failed :(\n");
        return 0;
    }

    new_n->object = object;
    new_n->next = NULL;

    if (q->root == NULL)
    {
        q->root = new_n;
        q->tail = new_n;
    }

    // update the tail to the new node
    else
    {
        q->tail->next = new_n;
        q->tail = new_n;
    }
    q->size++;
    pthread_mutex_unlock(&q->_lock);
    YELLOW;
    printf("Enqueue to queue number %d Succeeded\n",q->id);
    RESET;
    pthread_cond_broadcast(&q->_cond);
    return 0;
}
void *deQ(p_queue q)
{
    pthread_mutex_lock(&q->_lock);

    if (q->root == NULL)
    {
        GREEN;
        printf("Queue number %d is empty\n",q->id);
        printf("Waiting on condition variable _cond\n");
        RESET;
        pthread_cond_wait(&q->_cond, &q->_lock);
    }
    p_node curr = q->root;
    void *result = curr->object;
    q->root = q->root->next;

    if (q->root == NULL)
    {
        q->tail = NULL;
    }
    q->size--;
    pthread_mutex_unlock(&q->_lock);
    free(curr);
    YELLOW;
    printf("Dequeue from queue number %d Succeeded\n",q->id);
    RESET;
    return result;
}
int isEmpty(p_queue q){
    return (q->root==NULL);
}