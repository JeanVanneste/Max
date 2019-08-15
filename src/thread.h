#pragma once 

struct thread_max_st 
{
    int* data;
    int start_pos;
    int end_pos;
    int max;
};

void* local_max(void* arg); // find the maximum number between 2 position in a list


// ! Use only to find the maximum in a list that contain at least a positive integer
int find_global_max(int* data, int datasize, int thread_nb); // find the global max of a list of int
// return -1 in case of error during creation of a thread
// return -2 in case of error during join of thread