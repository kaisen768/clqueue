#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * Queue
 */
struct queue_t
{

   /**
    * Returns the number of elements in this collection.
    *
    * @param thiz this
    * @return the number of elements in this collection
    */
   uint32_t (*size)(const struct queue_t *thiz);

   /**
    * Removes all of the elements from this collection.
    *
    *  @param thiz this
    */
   void (*clear)(const struct queue_t *thiz);

   /**
    * Free collection
    *
    * @param thiz this
    */
   void (*free)(const struct queue_t *thiz);

   /** 
    * Inserts the specified element into this queue if it is possible to do
    * so immediately without violating capacity restrictions.
    *
    * @param thiz this
    * @param element element
    * @return true if the element was added to this queue, else false
    */
   bool (*offer)(const struct queue_t *thiz, const void *const element);

   /** 
    * Retrieves and removes the head of this queue,
    * or returns NULL if this queue is empty.
    *
    * @param thiz this
    * @return the head of this queue, or NULL if this queue is empty 
    */
   void *(*poll)(const struct queue_t *thiz);

   /** 
    * Retrieves, but does not remove, the head of this queue,
    * or returns NULL if this queue is empty.
    *
    * @param thiz this
    * @return the head of this queue, or NULL if this queue is empty
    */
   void *(*peek)(const struct queue_t *thiz);
};

#ifdef __cplusplus
}
#endif

#endif

