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
  size_t index = root - nodePool;
  printf("    Node_%zu\n", index);
  for (size_t i = 0; i < ARRAY_LEN(root->children); i++) {
    if (root->children[i] != NULL) {
      size_t childIndex = root->children[i] - nodePool;
      printf("    Node_%zu -> Node_%zu [label=%c]\n", index, childIndex,
             (char)i);

      if (root->children[i]->isEndOfWord) {
        // TODO: add an additional empty node to show the end of word
        // for words that overlap, i.e. are prefixes of another words there is
        // currently no obvious way to show this
      }

      dumpDot(root->children[i]);
    }
  }
}
