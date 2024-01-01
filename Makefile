CC = cc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -ggdb
TARGET = trie

.PHONY: all clean run

all: $(TARGET)

$(TARGET): main.c trie.c trie.h
	$(CC) $(CFLAGS) -o $(TARGET) main.c trie.c

run: $(TARGET)
	./$(TARGET) | dot -Tsvg | display

clean:
	rm -f $(TARGET)

