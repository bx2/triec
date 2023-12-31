#!/bin/sh
set -xe
cc -o trie trie.c -Wall -Wextra -pedantic -std=c11 -ggdb
./trie | dot -Tsvg | display
