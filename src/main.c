#include "main.h"
#include "trie.h"
#include "words.h"

void deallocate(Node **root)
{
    if ((*root) == NULL)
        return;

    // Base case
    if ((*root)->end == true)
        (*root)->end = false;

    for (int i = 0; i < ALPHABET_SIZE; ++i)
        deallocate(&(*root)->children[i]);

    free(*root);
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

// This is the entry point of the program
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
    if (strcmp(subcommand, "--help") == 0)
    {
        usage(stderr, program);
        deallocate(&root);
        exit(1);
    }
    // Dump trie into graphviz dot file
    else if (strcmp(subcommand, "dot") == 0)
    {
        char *output_filepath = "graphviz/trie.dot";
        printf("[INFO]: Generating %s\n", output_filepath);
        FILE *out = fopen(output_filepath, "w");
        if (out == NULL)
        {
            fprintf(stderr, "[ERROR]: Could not write to file %s\n", output_filepath);
            deallocate(&root);
            exit(1);
        }

        fprintf(out, "digraph Trie {\n");
        dumpRoot(out, root);
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
            exit(1);
        }
        else
        {
            // Convert prefix to lowercase
            for (size_t i = 0; i < strlen(prefix); ++i)
                prefix[i] = tolower(prefix[i]);

            // Search the prefix in the trie
            char *prefix_search = prefix;
            Node *end_of_prefix = searchPrefix(root, prefix_search, 0);
            if (end_of_prefix == NULL)
                printf("[INFO]: Prefix '%s' didn't found in trie\n", prefix);
            else
            {
                printf("[INFO]: Autocomplete versions for prefix '%s':\n", prefix);
                char str[ALPHABET_SIZE];
                autocompletePrefix(end_of_prefix, str, 0, prefix_search);
            }
        }
    }
    else
    {
        usage(stderr, program);
        fprintf(stderr, "[ERROR]: Command %s not recognized.\n", subcommand);
        deallocate(&root);
        exit(1);
    }

    deallocate(&root);
    return 0;
}
