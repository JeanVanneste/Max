#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include <pthread.h>

#include "thread.h"

struct thread_max_st 
{
    int* data;
    int start_pos;
    int end_pos;
    int max;
};

int find_global_max(int* data, int datasize, int thread_nb)
{
    // We set global_max to be the first element of data
    int global_max = data[0];

    int i;
    int ret; // variable used to register return value of pthread functions

    // using 2 array to store information on each thread
    pthread_t tid[thread_nb];
    struct thread_max_st thread_args[thread_nb];

    // Creation of the n-1 first threads
    for (i = 0; i < thread_nb - 1; i++)
    {
        thread_args[i].data = data;
        thread_args[i].start_pos = (datasize / thread_nb) * i;
        thread_args[i].end_pos = (datasize / thread_nb) * (i + 1) - 1;
        thread_args[i].max = global_max;

        ret = pthread_create(&(tid[i]), NULL, &local_max, &(thread_args[i]));
        if (ret == EAGAIN)
        {
            fprintf(stderr, "Insufficient ressources to create another thread\n");
            return -1;
        }
        else if (ret != 0)
        {
            fprintf(stderr, "Error during creation of thread %d", i);
            return -1;
        }            
    }

    // Creation of the last thread. The process is separated from the other because
    // the end position must correspond to the last number in data
    thread_args[i].data = data;
    thread_args[i].start_pos = (datasize / thread_nb) * i;
    thread_args[i].end_pos = datasize - 1;
    thread_args[i].max = 0;

    ret = pthread_create(&(tid[thread_nb - 1]), NULL, &local_max, &(thread_args[thread_nb - 1]));
    if (ret == EAGAIN)
    {
        fprintf(stderr, "Insufficient ressources to create another thread\n");
        return -1;
    }
    else if (ret == EINVAL || ret == EPERM)
    {
        fprintf(stderr, "Error during creation of last thread\n");
        return -1;
    }
    else if (ret == 0)
        printf("All thread were created successfully\n");
    else
    { 
        fprintf(stderr, "Unknown error\n");
        return -1;
    }

    // End of all threads
    for (i = 0; i < thread_nb; i++)
    {
        ret = pthread_join(tid[i], NULL);
        if (ret != 0)
        {
            fprintf(stderr, "Error during join of thread %d: ", i);
            if (ret == EINVAL)
                fprintf(stderr, "Another thread is already waiting to join child thread\n");
            else if (ret == ESRCH)
                fprintf(stderr, "No thread with the ID %lu could be fond\n", tid[i]);
            return -2;
        }
    }

    printf("All threads were closed successfully\n");

    // Compute all the local maximums to find the global max
    for (i = 0; i < thread_nb; i++)
    {
        if (thread_args[i].max > global_max)
            global_max = thread_args[i].max;
    }
    
    return global_max;
}

void* local_max(void* arg)
{
    struct thread_max_st* tp = (struct thread_max_st*) arg;

    for (int i = tp->start_pos; i <= tp->end_pos; i++)
    {
        if (tp->data[i] > tp->max)
            tp->max = tp->data[i];
    }

    pthread_exit(NULL);
}