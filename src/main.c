#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <raylib.h>

#include <tried/node.h>
#include <tried/world.h>




int main(void)
{
  SetConfigFlags(FLAG_FULLSCREEN_MODE);

  int monitor = GetCurrentMonitor();
  InitWindow(GetMonitorWidth(monitor), GetMonitorHeight(monitor), "Tried");

  SetTargetFPS(60);


  World* world = world_create((VisualNodeFactory){
    .color = WHITE,
    .radius = 15.0f,
    .string_length = 150.0f,
    .string_tension = 5.0f
  });
  world->drag_force = 4.0f;

  while (!WindowShouldClose())
  {
    world_update(world);


    BeginDrawing();
      ClearBackground(BLACK);


      world_draw(world);

    EndDrawing();
  }


  CloseWindow();

  return 0;
}
