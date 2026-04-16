#include <tried/world.h>

#include <stdlib.h>

#include <raymath.h>


#define MINIMUN_VELOCITY_EPSILON 0.001f




static void world_update_mouse_inputs(World* const world);
static void link_node_with_world(World* const world, VisualNode* const node);
static void visual_node_update_movement(VisualNode* const node);
static void visual_node_update_tension_movement(VisualNode* const node);
static void visual_node_update_mouse_dragging(VisualNode* const node);
static bool is_point_over_visual_node(const VisualNode* const node, const Vector2 mouse_position);
static void visual_node_apply_drag(VisualNode* const node, const float drag_force);




VisualNode* visual_node_create_from_factory(VisualNodeFactory factory, Vector2 position)
{
  return visual_node_create(position, factory.color, factory.radius, factory.string_tension, factory.string_length);
}




World* world_create(const VisualNodeFactory factory)
{
  World* world = calloc(1, sizeof(World));
  world->node_factory = factory;

  return world;
}


VisualNode* world_create_node(World* const world, const Vector2 position)
{
  VisualNode* node = visual_node_create_from_factory(world->node_factory, position);
  world_add_node(world, node);

  return node;
}




void world_update(World* const world)
{
  world_update_mouse_inputs(world);

  for (size_t i = 0; i < world->node_count; i++)
    visual_node_update(world->nodes[i], world);
}


static void world_update_mouse_inputs(World* const world)
{
  if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
  {
    VisualNode* node = world_create_node(world, GetMousePosition());
    link_node_with_world(world, node);
  }
}


static void link_node_with_world(World* const world, VisualNode* const node)
{
  for (size_t i = 0; i < world->node_count; i++)
    visual_node_link_dual(node, world->nodes[i]);
}


void visual_node_update(VisualNode* const node, const World* const world)
{
  visual_node_update_tension_movement(node);
  visual_node_apply_drag(node, world->drag_force);

  visual_node_update_movement(node);

  visual_node_update_mouse_dragging(node);
}


static void visual_node_update_movement(VisualNode* const node)
{
  node->velocity = Vector2Add(node->velocity, node->acceleration);
  node->acceleration = Vector2Zero();

  if (Vector2Length(node->velocity) < MINIMUN_VELOCITY_EPSILON)
    node->velocity = Vector2Zero();

  node->position = Vector2Add(node->position, node->velocity);
}


static void visual_node_update_tension_movement(VisualNode* const node)
{
  for (size_t i = 0; i < node->link_count; i++)
  {
    VisualNode* linked_node = (VisualNode*)node->links[i];
    float distance = Vector2Distance(node->position, linked_node->position);

    float average_string_length = (node->string_length + linked_node->string_length) / 2.0f;
    float average_string_tension = (node->string_tension + linked_node->string_tension) / 2.0f;

    float string_length_excess = (distance - average_string_length) / 100.0f;

    float force = average_string_tension * string_length_excess;
    Vector2 force_direction = Vector2Normalize(Vector2Subtract(linked_node->position, node->position));

    node->acceleration = Vector2Add(node->acceleration, Vector2Multiply(force_direction, (Vector2){ force, force }));
  }
}


static void visual_node_update_mouse_dragging(VisualNode* const node)
{
  if (is_point_over_visual_node(node, GetMousePosition()) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    node->is_being_dragged = true;

  if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    node->is_being_dragged = false;

  if (node->is_being_dragged)
    node->position = GetMousePosition();
}

static bool is_point_over_visual_node(const VisualNode* const node, const Vector2 mouse_position)
{
  return Vector2Distance(node->position, mouse_position) <= node->radius;
}


static void visual_node_apply_drag(VisualNode* const node, const float drag_force)
{
  Vector2 drag = Vector2Scale(node->velocity, -drag_force / 20.0f);
  node->acceleration = Vector2Add(node->acceleration, drag);
}




void world_draw(const World* const world)
{
  for (size_t i = 0; i < world->node_count; i++)
    visual_node_draw_link_lines(world->nodes[i]);

    for (size_t i = 0; i < world->node_count; i++)
    visual_node_draw(world->nodes[i]);
}


void visual_node_draw(const VisualNode* const node)
{
  DrawCircleV(node->position, node->radius, node->color);
}


void visual_node_draw_link_lines(const VisualNode* const node)
{
  for (size_t i = 0; i < node->link_count; i++)
    DrawLineV(node->position, node->links[i]->position, GRAY);
}




void world_add_node(World* const world, VisualNode* const node)
{
  world->nodes[world->node_count++] = node;
}