#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include "lb_queue.h"
#include "blocking_queue.h"

typedef struct _data_s {
    int num;
    char dat[32];
} _data_t;

void *thread_blocking_queue_take(void *arg)
{
    struct blocking_queue_t *queue = arg;

    int i;
    _data_t *pdat = NULL;

    if (!queue)
        return NULL;

    for (i = 0; i < 10000; i++) 
    {
        pdat = queue->take(queue);

        if (pdat) 
        {
            fprintf(stderr, "Block Queue Poll element : [%d]-%s\n", pdat->num, pdat->dat);
            free(pdat);
        }
    }

    /* current queue size */
    printf("Block Queue current size: %d\n", queue->size(queue));

    return NULL;
}

void *thread_blocking_queue_push(void *arg)
{
    struct blocking_queue_t *queue = arg;
    
    int i;
    int r;

    if (!queue)
        return NULL;

    sleep(3);

    for (i = 0; i < 10000; i++) 
    {
        _data_t *pdat = (_data_t*)malloc(sizeof(_data_t));

        pdat->num = i;
        sprintf(pdat->dat, ">>>>> %d", i);

        r = queue->put(queue, pdat);
        if (r == false)
        {
            fprintf(stderr, "Block Queue Push element <%d> failed!\n", i);
            free(pdat);
        }
    }

    return NULL;
}

int main(int argc, const char *argv[])
{
    pthread_t tid_p;
    pthread_t tid_t;

    struct blocking_queue_t *queue = lb_queue(128);

    pthread_create(&tid_p, NULL, thread_blocking_queue_push, queue);
    pthread_create(&tid_t, NULL, thread_blocking_queue_take, queue);

    pthread_join(tid_p, NULL);
    pthread_join(tid_t, NULL);

    return 0;
}

