CC = cc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -ggdb
TARGET = trie
OBJ = trie.o main.o

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

trie.o: trie.c trie.h
	$(CC) $(CFLAGS) -c trie.c

main.o: main.c trie.h
	$(CC) $(CFLAGS) -c main.c

run: $(TARGET)
	./$(TARGET) | dot -Tsvg | display

clean:
	rm -f $(TARGET) $(OBJ)
