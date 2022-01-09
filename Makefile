CC=gcc
CFLAGS=-g -Wall -o
SRC_DIR=./src
GRAPH_DIR=./graphviz
VALGRIND_FLAGS=--tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20

.PHONY: build graphviz autocomplete graphviz clean

build:
	$(CC) $(CFLAGS) trie $(SRC_DIR)/main.c $(SRC_DIR)/trie.c 

valgrind: build
	valgrind $(VALGRIND_FLAGS) ./trie dot

autocomplete: build
	@read -p "Enter the prefix: " prefix; ./trie complete $$prefix

graphviz: build
	./trie dot | dot -Tsvg $(GRAPH_DIR)/trie.dot > $(GRAPH_DIR)/output.svg

clean:
	rm trie
