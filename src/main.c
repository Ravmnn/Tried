#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <tried/node.h>

#include <raylib.h>




void validate_input(const char* const input);




int main(void)
{
  InitWindow(800, 600, "Tried");

  while (!WindowShouldClose())
  {
    BeginDrawing();

      ClearBackground(BLACK);


      DrawText("Hello, world!", 190, 200, 20, LIGHTGRAY);


    EndDrawing();
  }

  CloseWindow();

  return 0;
}
