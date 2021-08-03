#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lp_queue.h"
#include "queue.h"

typedef struct _data_s {
    int compare_num;    /* comparison variable */
    char dat[128];
} _data_t;


int32_t sort(const void *origin, const void *dest)
{
    _data_t *com_origin = (_data_t*)origin;
    _data_t *com_dest = (_data_t*)dest;

    if (com_origin->compare_num > com_dest->compare_num)
        return PQUEUE_PRIORITY_HIGHER;
    else if (com_origin->compare_num < com_dest->compare_num)
        return PQUEUE_PRIORITY_LOWER;
    else
        return PQUEUE_PRIORITY_EQUAL;
}

int main(int argc, const char *argv[])
{
    struct queue_t *queue = lp_queue(128, sort);
    int i;
    _data_t *dt;

    _data_t *d0  = malloc(sizeof(_data_t));
    d0->compare_num = 0;
    memcpy(d0->dat, ">>>> 0", strlen(">>>> 0"));

    queue->offer(queue, d0);

    _data_t *d1  = malloc(sizeof(_data_t));
    d1->compare_num = 5;
    memcpy(d1->dat, ">>>> 1", strlen(">>>> 1"));

    queue->offer(queue, d1);

    _data_t *d2  = malloc(sizeof(_data_t));
    d2->compare_num = 8;
    memcpy(d2->dat, ">>>> 2", strlen(">>>> 2"));

    queue->offer(queue, d2);

    _data_t *d3  = malloc(sizeof(_data_t));
    d3->compare_num = 2;
    memcpy(d3->dat, ">>>> 3", strlen(">>>> 3"));

    queue->offer(queue, d3);

    _data_t *d4  = malloc(sizeof(_data_t));
    d4->compare_num = 6;
    memcpy(d4->dat, ">>>> 4", strlen(">>>> 4"));

    queue->offer(queue, d4);

    _data_t *d5  = malloc(sizeof(_data_t));
    d5->compare_num = 2;
    memcpy(d5->dat, ">>>> 5", strlen(">>>> 5"));

    queue->offer(queue, d5);

    for (i = 0; i < 6; i++)
    {
        dt = queue->poll(queue);
        if (dt)
            printf("dt->compare_num<%d> dt->dat:%s  Queue-size:%d\n", dt->compare_num, dt->dat, queue->size(queue));
    }

    return 0;
}

