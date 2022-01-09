#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#ifndef _TRIE_
#define _TRIE_

#define ALPHABET_SIZE 256

typedef struct Node
{
    bool end;
    int index;
    struct Node *children[ALPHABET_SIZE];
} Node;

Node *newNode();
void insertWord(Node *root, const char *word);

void dfs(Node *root, int level);
void printTrie(FILE *out, Node *root);

Node *searchPrefix(Node *root, const char *prefix, size_t level);
void autocompletePrefix(Node *root, char *str, size_t level, char *prefix);

size_t getNodePoolCount();

#endif
