#ifndef _LP_QUEUE_H_
#define _LP_QUEUE_H_

#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <signal.h>
#include "queue.h"

#ifdef __cplusplus
extern "C" {
#endif

enum _pqueue_priority_e {
    PQUEUE_PRIORITY_EQUAL = 0,
    PQUEUE_PRIORITY_HIGHER = 1,
    PQUEUE_PRIORITY_LOWER = -1
};

struct queue_t *lp_queue(const uint32_t capacity, int32_t (*const compare)(const void *, const void *));

#ifdef __cplusplus
}
#endif

#endif

