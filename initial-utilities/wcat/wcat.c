#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    // Buffer for reading data
    size_t nbytes = 512;
    char* buffer = (char*)malloc(nbytes);
    if (buffer == NULL)
    {
        printf("wcat: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    // Loop through files and print contents if they exist
    for (int i = 1; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            printf("wcat: cannot open file\n");
            exit(EXIT_FAILURE);
        }
        
        while(fgets(buffer, nbytes, fp))
        {
            printf("%s", buffer);
        }

        fclose(fp);
    }

    // Free resources and exit
    free(buffer);
    return 0;
}