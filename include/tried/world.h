#pragma once

#include <stddef.h>

#include <tried/visual_node.h>


#define MAX_WORLD_NODES 512




typedef struct
{
  Color color;
  float radius;
  float string_length;
  float string_tension;
} VisualNodeFactory;


VisualNode* visual_node_create_from_factory(const VisualNodeFactory factory, const Vector2 position);




typedef struct
{
  VisualNodeFactory node_factory;

  VisualNode* nodes[MAX_WORLD_NODES];
  size_t node_count;

  float drag_force;
} World;


World* world_create(const VisualNodeFactory factory);
VisualNode* world_create_node(World* const world, const Vector2 position);


void world_update(World* const world);
void world_draw(const World* const world);

void visual_node_update(VisualNode* const visual_node, const World* const world);
void visual_node_draw(const VisualNode* const visual_node);

void world_add_node(World* const world, VisualNode* const node);