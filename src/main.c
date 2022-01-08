// This is the entry point of the program
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include "trie.h"
#include "fruits.h"

void deallocate(Node **root)
{
    printf("[TODO]: Deallocate trie memory\n");
}

int scc(int code, Node **root)
{
    if (code < 0)
    {
        fprintf(stderr, "ERROR: Return code %d\n", code);
        deallocate(root);
        exit(1);
    }

    return code;
}

void *scp(void *ptr, Node **root)
{
    if (ptr == NULL)
    {
        fprintf(stderr, "ERROR: Null pointer exception\n");
        deallocate(root);
        exit(1);
    }

    return ptr;
}

void usage(FILE *file, const char *program)
{
    fprintf(file, "Usage: %s [COMMAND] <ARGUMENTS>\n", program);
    fprintf(file, "COMMANDS:\n");
    fprintf(file, "     dot                   Dump the Trie into a Graphviz dot file.\n");
    fprintf(file, "     complete <prefix>     Suggest prefix autocompletion based on the Trie.\n");
}

int main(int argc, char *argv[])
{
    char *program = *argv++;
    if (*argv == NULL)
    {
        usage(stderr, program);
        fprintf(stderr, "[ERROR]: No command is provided.\n");
        exit(1);
    }

    // Loading the trie with some words
    Node *root = newNode();
    for (size_t i = 0; i < fruits_count; ++i)
        insertWord(root, fruits[i]);

    char *subcommand = *argv++;
    // Dump trie into graphviz dot file
    if (strcmp(subcommand, "dot") == 0)
    {
        char *output_filepath = "graphviz/trie.dot";
        printf("[INFO]: Generating %s\n", output_filepath);
        FILE *out = fopen(output_filepath, "w");
        if (out == NULL)
        {
            fprintf(stderr, "[ERROR]: Could not write to file %s\n", output_filepath);
            deallocate(&root);
        }

        fprintf(out, "digraph Trie {\n");
        printTrie(out, root);
        fprintf(out, "}\n");

        fclose(out);
        scc(system("dot -Tsvg graphviz/trie.dot > graphviz/output.svg"), &root);
        printf("[INFO]: Output available at graphviz/output.svg\n");
    }
    // Autocomplete a given prefix
    else if (strcmp(subcommand, "complete") == 0)
    {
        char *prefix = *argv++;
        if (prefix == NULL)
        {
            usage(stderr, program);
            fprintf(stderr, "[ERROR]: No prefix is provided.\n");
            deallocate(&root);
        }
        else
        {
            printf("[TODO]: Autocomplete for this prefix: %s\n", prefix);
            // Convert prefix to lowercase
            for (size_t i = 0; i < strlen(prefix); ++i)
                prefix[i] = tolower(prefix[i]);
        }
    }
    else
    {
        usage(stderr, program);
        fprintf(stderr, "[ERROR]: Command %s not recognized.\n", subcommand);
        deallocate(&root);
    }

    deallocate(&root);
    return 0;
}
