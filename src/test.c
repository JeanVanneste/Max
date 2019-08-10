#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

struct thread_param {
    int start_pos;
    int end_pos;
    int max;
};

void* local_max();

int main()
{
    int threads_nb = 3;

    unsigned int datasize = 10;

    int ret = 0;
    int i = 0;

    pthread_t tid[threads_nb];

    struct thread_param thread_args[threads_nb];

    printf("Creation of %d threads\n", threads_nb);
    
    for (i = 0; i < threads_nb - 1; i++)
    {
        thread_args[i].start_pos = (datasize / threads_nb) * i;
        thread_args[i].end_pos = (datasize / threads_nb) * (i + 1) - 1;
        thread_args[i].max = 0;

        ret = pthread_create(&(tid[i]), NULL, &local_max, &(thread_args[i]));
        if (ret == 0)
            printf("Thread %d created\n", i);
        else if (ret == EAGAIN)
        {
            printf("ERROR: Insufficient ressources to create another thread\n");
            return -1;
        }
        else if (ret == EINVAL || ret == EPERM)
        {
            printf("ERRROR: Unknown\n");
            return -1;
        }
    }

    thread_args[i].start_pos = (datasize / threads_nb) * (threads_nb - 1);
    thread_args[i].end_pos = datasize - 1;
    thread_args[i].max = 0;

    ret = pthread_create(&(tid[threads_nb - 1]), NULL, &local_max, &(thread_args[threads_nb - 1]));
    if (ret != 0)
    {
        printf("Error with last thread creation");
        return -1;
    }

    for (i = 0; i < threads_nb; i++)
    {       
        ret = pthread_join(tid[i], NULL);
        
        if (ret != 0)
        {
            printf("Error during join of thread %d: ", i);
            if (ret == EINVAL)
                printf("Another thread is already waiting to join child thread\n");
            else if (ret == ESRCH)
                printf("No thread with the ID %lu could be found\n", tid[i]);
            return -1;
        }
        else
            printf("Thread %d joined succesfully\n", i);
        
    }

    printf("All threads were closed succefully\n");

    return 0;
}

void* local_max(void* arg)
{
    struct thread_param* tp = (struct thread_param*) arg;

    printf("Start position = %d\n", tp->start_pos);
    printf("End position = %d\n", tp->end_pos);

    pthread_exit(NULL);
}