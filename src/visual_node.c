#include <tried/visual_node.h>

#include <stdlib.h>




VisualNode *visual_node_create(const Vector2 position, const Color color, const float radius, const float string_tension, const float string_length)
{
  VisualNode *node = calloc(1, sizeof(VisualNode));
  node->position = position;
  node->color = color;
  node->radius = radius;
  node->string_tension = string_tension;
  node->string_length = string_length;

  return node;
}


VisualNode* visual_node_create_default(const Vector2 position, const float string_tension, const float string_length)
{
  return visual_node_create(position, WHITE, 10.0f, string_tension, string_length);
}




void visual_node_link_dual(VisualNode* const node, VisualNode* const other)
{
  if (!visual_node_is_linked_to(node, other))
    visual_node_add_link(node, other);

  if (!visual_node_is_linked_to(other, node))
    visual_node_add_link(other, node);
}


bool visual_node_is_linked_to(const VisualNode* const node, const VisualNode* const other)
{
  for (size_t i = 0; i < node->link_count; i++)
    if (node->links[i] == other)
      return true;

  return false;
}


void visual_node_add_link(VisualNode* const node, VisualNode* const other)
{
  node->links[node->link_count++] = other;
}