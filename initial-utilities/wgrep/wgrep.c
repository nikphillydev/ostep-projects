#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
    // Check usage
    if (argc == 1)
    {
        printf("wgrep: searchterm [file ...]\n");
        exit(EXIT_FAILURE);
    }
    char* searchterm = argv[1];

    size_t nbytes = 1024;
    char* buffer = (char*)malloc(nbytes);
    if (buffer == NULL)
    {
        printf("wgrep: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    if (argc > 2) 
    {
        // Search through files to find match
        for (int i = 2; i < argc; i++)
        {
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL)
            {
                printf("wgrep: cannot open file\n");
                exit(EXIT_FAILURE);
            }

            while(getline(&buffer, &nbytes, fp) != -1)
            {
                if (strstr(buffer, searchterm))
                {
                    printf("%s", buffer);
                }
            }

            fclose(fp);
        }

    } else
    {
        // Search through stdin to find match
        while(getline(&buffer, &nbytes, stdin) != -1)
        {
            if (strstr(buffer, searchterm))
            {
                printf("%s", buffer);
            }
        }
    }

    // Free resources and exit
    free(buffer);
    return 0;
}