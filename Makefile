CC=gcc
CFLAGS=-g -Wall -pedantic -o
SRC_DIR=./src
GRAPH_DIR=./graphviz
VALGRIND_FLAGS=--tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20

.PHONY: build valgrind complete graphviz clean

build:
	$(CC) $(CFLAGS) trie $(SRC_DIR)/main.c $(SRC_DIR)/trie.c 

valgrind: build
	valgrind $(VALGRIND_FLAGS) ./trie dot

complete: build
	@read -p "Enter the prefix: " prefix;\
	./trie complete $$prefix

graphviz: build
	./trie dot

clean:
	rm trie
