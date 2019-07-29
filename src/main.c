#include <sys/types.h>
#include <sys/stat.h>

#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#define NUM_MAX_LENGTH 6

unsigned int count_lines(const char *filename);
int* read_file_to_array(const char* filename, int size);
int convert_array_to_int(char* number, int size);

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Il y a %d arguments\n", argc);
        printf("Il manque des arguments\n");
        return 1;
    }
    const char* filename = argv[1];
    unsigned int line_count = count_lines(filename);
    printf("Nombre de lignes : %d\n", line_count);

    
    int *data = read_file_to_array(filename, line_count);
    for (int i = 0; i < line_count; i++)
    {
        printf("%d\n", data[i]);
    }   
    
    int max = 0; 

    for (int i = 0; i < line_count; i++)
    {
        if (data[i] > max) { max = data[i]; }
    }
    printf("%d\n", max);
}

unsigned int count_lines(const char* filename)
{
    int file;
    unsigned int line_count = 0;
    if ((file = open(filename, O_RDONLY)) != -1)
    {
        char buffer[1];
        ssize_t s;
        while ((s = read(file, buffer, 1)) != 0)
        {
            if (*buffer == '\n')
                line_count++;
        }
        close(file);
    }

    return line_count;
}

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