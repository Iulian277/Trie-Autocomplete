#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "trie.h"

int scc(int code, Node **root);    // Check return code of a function
void *scp(void *ptr, Node **root); // Check if returned pointer of a function is NULL
void deallocate(Node **root);