CC=gcc
CFLAGS=-g -Wall -o
SRC_DIR=./src

build:
	$(CC) $(CFLAGS) trie $(SRC_DIR)/main.c $(SRC_DIR)/trie.c 

graphviz:
	trie > input.dot | dot -Tsvg input.dot > output.svg

clean:
	rm trie
