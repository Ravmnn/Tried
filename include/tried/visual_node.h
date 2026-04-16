#pragma once

#include <stddef.h>

#include <raylib.h>


#define MAX_VISUAL_NODE_LINKS 256




struct Node;


typedef struct VisualNode
{
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    bool is_being_dragged;

    Color color;
    float radius;

    float string_tension;
    float string_length;

    struct VisualNode* links[MAX_VISUAL_NODE_LINKS];
    size_t link_count;
} VisualNode;


VisualNode* visual_node_create(const Vector2 position, const Color color, const float radius, const float string_tension, const float string_length);
VisualNode* visual_node_create_default(const Vector2 position, const float string_tension, const float string_length);

void visual_node_link_dual(VisualNode* const node, VisualNode* const other);
bool visual_node_is_linked_to(const VisualNode* const node, const VisualNode* const other);

void visual_node_add_link(VisualNode* const node, VisualNode* const other);