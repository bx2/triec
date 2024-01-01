#include "trie.h"

int main(void) {
  Node *root = allocNode();
  insertText(root, "hello");
  insertText(root, "help");
  insertText(root, "helper");
  insertText(root, "heaven");
  insertText(root, "hell");
  insertText(root, "helium");
  insertText(root, "test");
  insertText(root, "tempo");
  insertText(root, "temporary");
  insertText(root, "temperature");
  insertText(root, "trick");
  insertText(root, "trie");
  printf("digraph {\n");
  dumpDot(root);
  printf("}\n");
  return 0;
}
