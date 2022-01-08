#include "main.h"
#include "trie.h"

size_t node_pool_count = 0; // Total current nodes in the trie
Node *newNode()
{
    Node *node = (Node *)scp(calloc(1, sizeof(Node)), NULL);
    node->end = false;
    node->index = node_pool_count++;

    return node;
}

// Each node has a fixed value in the 'node_pool' array
void insertWord(Node *root, const char *word)
{
    assert(root != NULL);

    if (word == NULL || *word == '\0')
    {
        root->end = true;
        return;
    }

    size_t index = (size_t)*word;
    // Convert everything to lowercase
    if (isupper(*word))
        index += 32;
    if (root->children[index] == NULL)
        root->children[index] = newNode();

    insertWord(root->children[index], word + 1);
}

void printTrie(FILE *out, Node *root)
{
    size_t index = root->index;
    for (size_t i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (root->children[i] != NULL)
        {
            size_t child_index = root->children[i]->index;
            fprintf(out, "\tNode_%zu [label=\"%c\"", child_index, (char)i);
            if (root->children[i]->end)
                fprintf(out, " shape=\"doublecircle\"");
            fprintf(out, "]\n");
            fprintf(out, "\tNode_%zu -> Node_%zu\n", index, child_index);
            printTrie(out, root->children[i]);
        }
    }
}

size_t getNodePoolCount()
{
    return node_pool_count;
}

void display(Node *root, char str[], int level)
{
    if (root->end)
    {
        str[level] = '\0';
        printf("%s\n", str);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            str[level] = i;
            display(root->children[i], str, level + 1);
        }
    }
}