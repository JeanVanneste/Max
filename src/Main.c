//#include <sys/types.h>
//#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>

#include <unistd.h>

#define BUFSIZE 1

int main() 
{
    int data_file;
    int line_count = 0;
    if ((data_file = open("data", O_RDONLY)) != -1)
    {
        char buffer[BUFSIZE];
        ssize_t s;
        while ((s = read(data_file, buffer, BUFSIZE)) != 0)
        {
            if (*buffer == '\n')
                line_count++;
        }
        close(data_file);
    }
    printf("%d\n", line_count);
}