#include <stdio.h>
#include <stdlib.h>
#include "lb_queue.h"
#include "blocking_queue.h"

typedef struct _data_s {
    char name[32];
    int numb;
} _data_t;

void blocking_queue_calling(struct blocking_queue_t *queue)
{
    int i;
    int size;
    _data_t *pout = NULL;

    _data_t d[5] = {
        {"data - 0", 0},
        {"data - 1", 1},
        {"data - 2", 2},
        {"data - 3", 3},
        {"data - 4", 4},
    };

    if (!queue)
        return;

    /* in queue */
    for (i = 0; i < 5; i++) 
    {
        queue->offer(queue, &d[i]);
    }

    size = queue->size(queue);
    printf("queue size[%d]\n", size);

    /* out queue */
    for (i = 0; i < size; i++) 
    {
        pout = (_data_t*)queue->poll(queue);
        printf("data index-<%d>   address:%p\n", i, pout);

        if (pout) 
            printf("data index-<%d>   name:%s  numb:%d\n", i, pout->name, pout->numb);
    }
}

int main(int argc, const char *argv[])
{
    struct blocking_queue_t *queue;

    queue = lb_queue(512);

    blocking_queue_calling(queue);

    queue->free(queue);

    return 0;
}

