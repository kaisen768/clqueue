#ifndef _LB_QUEUE_H_
#define _LB_QUEUE_H_

#include <stdint.h>
#include "blocking_queue.h"

#ifdef __cplusplus
extern "C" {
#endif

extern struct blocking_queue_t *lb_queue(const uint32_t capacity);

#ifdef __cplusplus
}
#endif

#endif

