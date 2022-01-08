CC=gcc
CFLAGS=-g -Wall -o

build:
	$(CC) $(CFLAGS) main main.c trie.c 

graphviz:
	./main > input.dot | dot -Tsvg input.dot > output.svg

clean:
	rm main
