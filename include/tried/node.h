#pragma once

#include <stddef.h>

#define MAX_WORD_LENGTH 50
#define MAX_NODE_CHILDREN 16




typedef struct Node
{
  struct Node* parent;
  struct Node* children[MAX_NODE_CHILDREN];
  size_t children_count;

  char character;

  bool is_end_of_word;
} Node;


bool is_word_valid(const char *word);
bool is_node_linear(const Node* const node);

Node* node_create(Node* const parent, const char character);
Node* node_create_from_word(const char* word);

void node_add_child(Node* const parent, Node* const child);

void node_merge(Node* const target, Node** const sources, const int nodes_count);