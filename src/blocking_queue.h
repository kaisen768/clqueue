#ifndef _BLOCKING_QUEUE_H_
#define _BLOCKING_QUEUE_H_

#include <stdint.h>
#include <stdbool.h>
#include "time_unit.h"

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * Blocking Queue
 */
struct blocking_queue_t {
    
    /** 
     * Returns the number of elements in this collection.
     *
     * @param thiz this
     * @return the number of elements in this collection
     */
    uint32_t (*size)(struct blocking_queue_t * const thiz);

    /**
     * Removes all of the elements from this collection.
     *
     *  @param thiz this
     */
    void (*clear)(struct blocking_queue_t * const thiz);

    /**
     * Free collection
     *
     * @param thiz this
     */
    void (*free)(struct blocking_queue_t * const thiz);

    /** 
     * Inserts the specified element into this queue if it is possible to do
     * so immediately without violating capacity restrictions.
     *
     * @param thiz this
     * @param element element
     * @return true if the element was added to this queue, else false
     */
    bool (*offer)(struct blocking_queue_t * const thiz, const void *element);

    /** 
     * Retrieves and removes the head of this queue,
     * or returns NULL if this queue is empty.
     *
     * @param thiz this
     * @return the head of this queue, or NULL if this queue is empty 
     */
    void *(*poll)(struct blocking_queue_t * const thiz);

    /** 
     * Retrieves, but does not remove, the head of this queue,
     * or returns NULL if this queue is empty.
     *
     * @param thiz this
     * @return the head of this queue, or NULL if this queue is empty
     */
    void *(*peek)(struct blocking_queue_t * const thiz);

    /**
     * Inserts the specified element into this queue, waiting if necessary for space to become available.
     *
     * @param thiz this
     * @param element the element to add
     * @return true if the element was added to this queue, else false
     */
    bool (*put)(struct blocking_queue_t * const thiz, const void *element);

    /** 
     * Inserts the specified element into this queue, waiting up to the
     * specified wait time if necessary for space to become available.
     *
     * @param thiz this
     * @param element the element to add
     * @param timeout how long to wait before giving up, in units of unit
     * @param unit a time_unit_t determining how to interpret the timeout parameter
     * @return true if successful, or false if the specified waiting time elapses before space is available
     */
    bool (*offer_await)(struct blocking_queue_t * const thiz, const void *element, const uint64_t timeout, const struct time_unit_t *unit);
    
    /** 
     * Retrieves and removes the head of this queue, waiting if necessary until an element becomes available.
     *
     * @param thiz this
     * @return the head of this queue
     */
    void *(*take)(struct blocking_queue_t * const thiz);

    /** 
     * Retrieves and removes the head of this queue, waiting up to the
     * specified wait time if necessary for an element to become available.
     *
     * @param thiz this
     * @param timeout how long to wait before giving up, in units of unit
     * @param unit a time_unit_t determining how to interpret the timeout parameter
     * @return the head of this queue, or NULL if the specified waiting time elapses before an element is available
     */
    void *(*poll_await)(struct blocking_queue_t * const thiz, const uint64_t timeout, const struct time_unit_t *unit);
};

#ifdef __cplusplus
}
#endif

#endif
