#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <sys/stat.h>

struct node
{
    struct node *prev;
    struct node *next;
    char *buffer;
    size_t nbytes;
};

void init_node(struct node *node)
{
    node->prev = NULL;
    node->next = NULL;
    node->buffer = NULL;
    node->nbytes = 0;
}

int main(int argc, char *argv[])
{
    FILE *in = NULL;
    FILE *out = NULL;

    if (argc == 1)
    {
        in = stdin;
        out = stdout;
    }
    else if (argc == 2)
    {
        in = fopen(argv[1], "r");   // Open input file
        if (in == NULL)
        {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
            exit(EXIT_FAILURE);
        }
        out = stdout;
    }
    else if (argc == 3)
    {
        in = fopen(argv[1], "r");   // Open input file
        if (in == NULL)
        {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
            exit(EXIT_FAILURE);
        }

        out = fopen(argv[2], "w");  // Open output file
        if (out == NULL)
        {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[2]);
            exit(EXIT_FAILURE);
        }

        struct stat stat1, stat2;   // Check if files hardlinked
        stat(argv[1], &stat1);
        stat(argv[2], &stat2);
        if (stat1.st_ino == stat2.st_ino)
        {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(EXIT_FAILURE);
    }

    // Create the initial node in the linked list
    struct node *curr = (struct node *)malloc(sizeof(struct node));
    if (curr == NULL)
    {
        fprintf(stderr, "reverse: malloc failed\n");
        exit(EXIT_FAILURE);
    }
    init_node(curr);

    while (getline(&curr->buffer, &curr->nbytes, in) != EOF)     // Get a line of input, store in current node
    {
        // Create the next node in the linked list
        struct node *next = (struct node *)malloc(sizeof(struct node));
        if (next == NULL)
        {
            fprintf(stderr, "reverse: malloc failed\n");
            exit(EXIT_FAILURE);
        }
        init_node(next);

        next->prev = curr;  // Connect next node to the linked list
        curr->next = next;
        curr = next;        // Set the next node to the current node
    }

    while (curr->prev != NULL)  // Loop until at head node
    {
        if (curr->nbytes != 0)
        {
            fprintf(out, "%s", curr->buffer);
        }
        curr = curr->prev;
        free(curr->next->buffer);   // Free node's buffer, free node itself
        free(curr->next);
    }
    if (curr->nbytes != 0)
    {
        fprintf(out, "%s", curr->buffer);
    }
    free(curr->buffer);
    free(curr);
    
    return 0;
}