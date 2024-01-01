#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>
#include <stdio.h>

#define NODE_POOL_CAP 1024
#define MAX_CHILDREN 256

#define ARRAY_LEN(arr) (sizeof(arr) / sizeof(arr[0]))

typedef struct Node Node;
struct Node {
  bool isEndOfWord;
  Node *children[MAX_CHILDREN];
};

Node *allocNode(void);
void insertText(Node *, const char *);
void dumpDot(Node *);

#endif
