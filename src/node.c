#include <tried/node.h>

#include <stdlib.h>




static void merge_linear_nodes(Node* current_target, Node* current_source);
static bool add_child_if_branch(Node* const target, Node* const source);




bool is_word_valid(const char* const word)
{
  if (!word)
    return false;

  for (const char* ch = (const char*)word; *ch; ch++)
    if (*ch < 'a' || *ch > 'z')
      return false;

  return true;
}




bool is_node_linear(const Node* const node)
{
  if (!node)
    return false;

  if (node->children_count > 1)
    return false;

  if (node->children_count == 0)
    return true;

  return is_node_linear(node->children[0]);
}




Node* node_create(Node* const parent, const char character)
{
  Node* node = calloc(1, sizeof(Node));
  node->character = character;

  node_add_child(parent, node);

  return node;
}


Node* node_create_from_word(const char* word)
{
  if (!is_word_valid(word))
    return NULL;

  Node* root = node_create(NULL, *word);
  Node* current = root;

  while (*word++)
    current = node_create(current, *word);

  current->is_end_of_word = true;
  return root;
}




void node_add_child(Node* const parent, Node* const child)
{
  if (!parent || !child || parent->children_count >= MAX_NODE_CHILDREN_LENGTH)
    return;

  child->parent = parent;
  parent->children[parent->children_count++] = (Node*)child;
}




void node_merge(Node* const target, Node** const sources, const int nodes_count)
{
  if (!is_node_linear(target))
    return;

  for (int i = 0; i < nodes_count; i++)
  {
    Node* current_target = target;
    Node* current_source = sources[i];

    if (!is_node_linear(current_source) || current_source->character != current_target->character)
      continue;

    merge_linear_nodes(current_target, current_source);
  }
}


static void merge_linear_nodes(Node* current_target, Node* current_source)
{
  do
  {
    if (add_child_if_branch(current_target, current_source))
      break;

    if (current_target->children_count == 0 || current_source->children_count == 0)
      break;

    current_target = current_target->children[0];
    current_source = current_source->children[0];
  } while (!current_target->is_end_of_word);
}


static bool add_child_if_branch(Node* const target, Node* const source)
{
  if (target->character != source->character)
  {
    node_add_child(target->parent, source);
    return true;
  }

  return false;
}