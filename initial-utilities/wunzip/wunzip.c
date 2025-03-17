#include "stdio.h"
#include "stdlib.h"

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("wunzip: file1 [file2 ...]\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            printf("wunzip: cannot open file\n");
            exit(EXIT_FAILURE);
        }

        int count = 0;
        char letter = '\0';

        while (fread(&count, 4, 1, fp))
        {
            fread(&letter, 1, 1, fp);
            for (int j = 0; j < count; j++)
            {
                printf("%c", letter);
            }
        }
    }

    return 0;
}