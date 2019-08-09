#include "local_max.h"

void* local_max(void* arg)
{
    //struct thread_param* tp = (struct thread_param*) arg;

    printf("from thread\n");
    
    int count = 0;
    for (int i =0; i < 100000000; i++)
        count++;

    pthread_exit(NULL);
}