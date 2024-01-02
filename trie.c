#include "trie.h"
#include <assert.h>
#include <stdio.h>

Node nodePool[NODE_POOL_CAP];
size_t nodePoolCount = 0;

Node *allocNode(void) {
  assert(nodePoolCount < NODE_POOL_CAP);
  return &nodePool[nodePoolCount++];
}

void insertText(Node *root, const char *text) {
  if (text == NULL || *text == '\0') {
    root->isEndOfWord = true;
    return;
  }

  assert(root != NULL);
  size_t index = (size_t)*text;

  if (root->children[index] == NULL)
    root->children[index] = allocNode();

  insertText(root->children[index], text + 1);
}

void dumpDot(Node *root) {
  static size_t emptyNodeCounter = 0;
  size_t index = root - nodePool;
  printf("\tNode_%zu\n", index);

  for (size_t i = 0; i < ARRAY_LEN(root->children); i++) {
    if (root->children[i] != NULL) {
      size_t childIndex = root->children[i] - nodePool;
      printf("\tNode_%zu -> Node_%zu [label=%c]\n", index, childIndex, (char)i);

      // Add an additional empty node to show the end of word
      if (root->children[i]->isEndOfWord) {
        printf("\tNode_%zu -> EmptyNode_%zu [style=dotted]\n", childIndex,
               emptyNodeCounter);
        printf("\tEmptyNode_%zu [label=\"%zu\", shape=none]\n",
               emptyNodeCounter, emptyNodeCounter);
        emptyNodeCounter++;
      }

      dumpDot(root->children[i]);
    }
  }
}
