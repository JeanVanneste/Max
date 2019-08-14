#define _GNU_SOURCE only
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>

#include <errno.h>

#include "thread.h"

#define NUM_MAX_LENGTH 6

unsigned int count_lines(const char *filename);
int* read_file_to_array(const char* filename, unsigned int* line_count);
void write_to_file(int max, const char* filename);
int convert_array_to_int(char* number, int size);
char* convert_int_to_array(int num);

int main(int argc, char* argv[])
{
    // Veriying that the user has provided 3 arguments
    if (argc < 2)
    {
        printf("Il y a %d arguments\n", argc);
        printf("Il manque des arguments\n");
        return 1;
    }
    // Parsing arguments
    const char* filename = argv[1];
    int thread_nb = atoi(argv[2]);

    // Writing data into an array
    unsigned int line_count = 0;
    int *data = read_file_to_array(filename, &line_count);
    printf("Nombre de lignes : %d\n", line_count);


    // Find the global max in the list with error detection
    int max = find_global_max(data, line_count, thread_nb);
    if (max == -1)
    {
        fprintf(stderr, "Error during creation of thread\n");
        return -1;
    }
    else if (max == -2)
    {
        fprintf(stderr, "Error during join of threads\n");
        return -1;
    }
    // If maxium is found, it is written in the result file
    write_to_file(max, argv[3]);

    free(data);
}

// Read all the character of a file and count the number of newline character (\n)
int* read_file_to_array(const char* filename, unsigned int* line_count)
{
    int file;
    unsigned int size = 1;
    int* data = calloc(size, sizeof(int));

    int i = 0; // itérateur des nombres
    int k = 0; // itérateur des digits
    
    if ((file = open(filename, O_RDONLY)) != -1)
    {
        char buffer[1];
        ssize_t s;
        char number[NUM_MAX_LENGTH];
        while ((s = read(file, buffer, 1)) != '\0')
        {
            if (*buffer == '\n')
            {
                (*line_count)++;
                data[i] = convert_array_to_int(number, k);
                if (i == size)
                {
                    data = reallocarray(data, size*2, sizeof(int));
                    size *= 2;
                    if (errno == ENOMEM)
                    {
                        fprintf(stderr, "ERROR: memory overflow\n");
                        return NULL;
                    }
                }
                i++;
                k = 0;
            }
            else
            {
                number[k] = (int)*buffer;
                k++;
            }
        }
        close(file);
    }

    //data = realloc(data, *line_count);

    return data;
}


/*Store the numbers from inside a file in an array
int* read_file_to_array(const char* filename, int size)
{
    int *data = malloc(size * sizeof(int));
    int file;
    if ((file = open(filename, O_RDONLY)) != -1)
    {
        char buffer[1];
        ssize_t s;
        char number[NUM_MAX_LENGTH];
        int i = 0;
        int k = 0;
        while ((s = read(file, buffer, 1)) != 0)
        {
            if (*buffer == '\n')
            {
                data[i] = convert_array_to_int(number, k);
                i++;
                k = 0;
            }
            else
            {
                number[k] = (int)*buffer;
                k++;
            }
        }
    }
    close(file);

    return data;
}
*/

// write a number to a file
void write_to_file(int max, const char* filename)
{
    int file;
    if ((file = open(filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IROTH)) != -1)
    {
        char* max_str = convert_int_to_array(max);
        write(file, max_str, NUM_MAX_LENGTH);
        write(file, "\n", 1);
        free(max_str);
    }
    else
    {
        fprintf(stderr, "Can't open destination file, check permissions\n");
    }
}


int convert_array_to_int(char* number, int size)
{
    int mul = 1;
    int result = 0;
    for (int i = size - 1; i >= 0; i--)
    {
        result += (int)(number[i] - '0') * mul;
        mul *= 10;
    }
    return result;
}

char* convert_int_to_array(int num)
{
    int size = 0;
    int num_copy = num;
    while (num_copy > 0)
    {
        num_copy /= 10;
        size++;
    }

    char *array = calloc(size, sizeof(char));

    for (int i = size - 1; i >= 0; i--)
    {
        array[i] = '0' + (num % 10);
        num /= 10;
    }

    return array;
}
