#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <errno.h>
#include <string.h>
#include "lp_queue.h"

/** 
 * queue node structure
 */
struct _node_t
{
    const void *item;
    struct _node_t *next;
};

/** 
 * list priority queue
 * 
 * priority queue based on linked list
 */
struct lp_queue_t
{

    /** 
     * Returns the number of elements in this collection.
     *
     * @param thiz this
     * @return the number of elements in this collection
     */
    uint32_t (*size)(struct lp_queue_t *const thiz);

    /**
     * Removes all of the elements from this collection.
     *
     *  @param thiz this
     */
    void (*clear)(struct lp_queue_t *const thiz);

    /**
     * Free collection
     *
     * @param thiz this
     */
    void (*free)(struct lp_queue_t *const thiz);

    /** 
     * Inserts the specified element into this queue if it is possible to do
     * so immediately without violating capacity restrictions.
     *
     * @param thiz this
     * @param element element
     * @return true if the element was added to this queue, else false
     */
    bool (*offer)(struct lp_queue_t *const thiz, const void *const element);

    /** 
     * Retrieves and removes the head of this queue,
     * or returns NULL if this queue is empty.
     *
     * @param thiz this
     * @return the head of this queue, or NULL if this queue is empty 
     */
    void *(*poll)(struct lp_queue_t *const thiz);

    /** 
     * Retrieves, but does not remove, the head of this queue,
     * or returns NULL if this queue is empty.
     *
     * @param thiz this
     * @return the head of this queue, or NULL if this queue is empty
     */
    void *(*peek)(struct lp_queue_t *const thiz);

    /*  queue sort condition function */
    int32_t (*_compare)(const void *, const void *);

    /* queue capacity */
    uint32_t _capacity;

    /* Number of queue elements */
    uint32_t _count;

    /* queue head node pointer */
    struct _node_t *_head;
};

#define QUEUE_MAX_CAPACITY 0xFFFFFFFFU

static inline void _enqueue(struct lp_queue_t *const thiz, struct _node_t *const node)
{
    struct _node_t *tmp = thiz->_head->next;
    struct _node_t *prev = thiz->_head;
    for (; tmp != NULL;)
    {
        if (thiz->_compare(tmp->item, node->item) > 0)
            break;

        prev = prev->next;
        tmp = tmp->next;
    }

    if (!tmp)
    {
        prev->next = node;
    }
    else
    {
        node->next = tmp;
        prev->next = node;
    }
}

static inline void *_dequeue(struct lp_queue_t *const thiz)
{
    struct _node_t *h = thiz->_head;
    struct _node_t *first = h->next;
    h->next = NULL;
    thiz->_head = first;
    void *x = (void *)first->item;
    first->item = NULL;

    free(h);
    return x;
}

static uint32_t lp_queue_size(struct lp_queue_t *const thiz)
{
    return thiz->_count;
}

static void lp_queue_clear(struct lp_queue_t *const thiz)
{
    if (!thiz)
    {
        errno = ENOMEM;
        return;
    }

    if (thiz->_count == 0)
        return;

    for (struct _node_t *t, *p = thiz->_head->next; p != NULL;)
    {
        t = p;
        p = t->next;

        if (t->item)
            free((void *)t->item);
        free(t);
    }

    thiz->_count = 0;

    return;
}

static void lp_queue_free(struct lp_queue_t *const thiz)
{
    if (!thiz)
    {
        errno = ENOMEM;
        return;
    }

    thiz->clear(thiz);

    free(thiz->_head);
    free(thiz);
}

static bool lp_queue_offer(struct lp_queue_t *const thiz, const void *const element)
{
    if (!thiz || !element)
    {
        errno = EINVAL;
        return false;
    }

    if (thiz->_count == thiz->_capacity)
        return false;

    struct _node_t *new_node = (struct _node_t *)malloc(sizeof(struct _node_t));
    if (!new_node)
    {
        errno = ENOMEM;
        return false;
    }
    new_node->item = element;
    new_node->next = NULL;

    _enqueue(thiz, new_node);

    thiz->_count++;

    return true;
}

static void *lp_queue_poll(struct lp_queue_t *const thiz)
{
    if (!thiz)
    {
        errno = ENOMEM;
        return NULL;
    }

    if (thiz->_count == 0)
        return NULL;

    void *item = _dequeue(thiz);

    thiz->_count--;

    return item;
}

static void *lp_queue_peek(struct lp_queue_t *const thiz)
{
    if (!thiz)
    {
        errno = ENOMEM;
        return NULL;
    }

    if (thiz->_count == 0)
        return NULL;

    void *item = NULL;
    item = thiz->_count > 0 ? (void *)thiz->_head->next : NULL;

    return item;
}

struct queue_t *lp_queue(const uint32_t capacity, int32_t (*const compare)(const void *, const void *))
{
    struct lp_queue_t *thiz = (struct lp_queue_t *)malloc(sizeof(struct lp_queue_t));
    if (!thiz)
    {
        errno = ENOMEM;
        goto lpQueue_err_0;
    }

    memset((void *)thiz, 0, sizeof(struct lp_queue_t));

    thiz->_capacity = (capacity == 0) ? QUEUE_MAX_CAPACITY : capacity;

    thiz->_head = (struct _node_t *)malloc(sizeof(struct _node_t)); /* singly linked list with head node */
    if (!thiz->_head)
    {
        errno = ENOMEM;
        goto lpQueue_err_1;
    }
    thiz->_count = 0;

    /* methods */
    thiz->size = lp_queue_size;
    thiz->clear = lp_queue_clear;
    thiz->free = lp_queue_free;
    thiz->offer = lp_queue_offer;
    thiz->poll = lp_queue_poll;
    thiz->peek = lp_queue_peek;
    thiz->_compare = compare;

    goto lpQueue_err_0;

lpQueue_err_1:
    free(thiz);
    thiz = NULL;

lpQueue_err_0:
    return (struct queue_t *)thiz;
}

