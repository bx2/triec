#include <assert.h>
#include <stdio.h>

#define ARRAY_LEN(arr) (sizeof(arr) / sizeof(arr[0]))

// we will block 256kb in memory
#define NODE_POOL_CAP 1024
#define MAX_CHILDREN 256

typedef struct Node Node;
struct Node {
  Node *children[MAX_CHILDREN];
};

Node nodePool[NODE_POOL_CAP] = {0};
size_t nodePoolCount = 0;

Node *allocNode(void) {
  assert(nodePoolCount < NODE_POOL_CAP);
  return &nodePool[nodePoolCount++];
}

void insertText(Node *root, const char *text) {
  if (text == NULL || *text == '\0')
    return;

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
      dumpDot(root->children[i]);
    }
  }
}

int main(void) {
  Node *root = allocNode();
  insertText(root, "hello");
  insertText(root, "help");
  insertText(root, "hell");
  insertText(root, "heaven");
  insertText(root, "helium");
  printf("digraph {\n");
  dumpDot(root);
  printf("}\n");
  return 0;
}
