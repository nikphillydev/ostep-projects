#include "stdio.h"
#include "stdlib.h"

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("wzip: file1 [file2 ...]\n");
        exit(EXIT_FAILURE);
    }

    int prev_char = EOF, curr_char = EOF, count = 1; 

    for (int i = 1; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            printf("wzip: cannot open file\n");
            exit(EXIT_FAILURE);
        }

        while((curr_char = fgetc(fp)) != EOF)
        {
            if (curr_char == prev_char)
            {
                count++;
            }
            else if (prev_char != EOF)
            {
                fwrite(&count, 4, 1, stdout);
                fwrite(&prev_char, 1, 1, stdout);
                count = 1;
            }
            prev_char = curr_char;
        }

        fclose(fp);
    }

    fwrite(&count, 4, 1, stdout);
    fwrite(&prev_char, 1, 1, stdout);

    return 0;
}