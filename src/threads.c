#include "threads.h"

struct thread_param {
    int start_pos;
    int end_pos;
    int max;
};

int main()
{
    int datasize = 10;
    int threads_nb = 2;

    char threads_max = get_nprocs();

    if (threads_nb > threads_max)
    {
        printf("Max thread is %d, only %d will be used\n", threads_max, threads_max);
        threads_nb = threads_max;
    }

    int ret = 0;

    pthread_t tid[threads_nb];

    struct thread_param thread_args[threads_nb];

    printf("Creation of %d threads\n", threads_nb);
    for (int i = 0; i < threads_nb - 1; i++)
    {
        thread_args[i].start_pos = (datasize / threads_nb) * (i) + 1;
        thread_args[i].end_pos = (datasize / threads_nb) * (i + 1); 
        thread_args[i].max = 0;
        
        ret = pthread_create(&(tid[i]), NULL, &local_max, &(thread_args[i]));
        if (ret != 0)
            break;
        else
            printf("Thread %d created\n",i);
    }
    //printf("%d\n", ret);
    if (ret == EAGAIN)
    {
        printf("Error, insufficient ressources to create another thread");
        return 1;
    }
    else if (ret == EINVAL || ret == EPERM)
    {
        printf("Error, invalid settings in attr.");
        return 1;
    }
    
    thread_args[threads_nb].start_pos = (datasize / threads_nb) * (threads_nb - 1) + 1;
    thread_args[threads_nb].end_pos = datasize - 1;
    thread_args[threads_nb].max = 0;
    
    ret = pthread_create(&(tid[threads_nb-1]), NULL, &local_max, &(thread_args[threads_nb-1]));

    if (ret != 0)
        return -1;
    else
        printf("Thread %d created\n",threads_nb - 1);
    
    for (int i = 0; i < threads_nb; i++)
    {
        ret = pthread_join(tid[i], NULL);
        if (ret != 0 )
        {
            printf("Error during join of thread %d: ", i);
            if (ret == EINVAL)
                printf("Another thread is already waiting to join with this thread\n");
            else if (ret == ESRCH)
                printf("No thread with the ID %lu could be found\n", tid[i]);
            return 1;
        }
        else
            printf("Thread %d finished succesfully\n", i+1);
    }
}