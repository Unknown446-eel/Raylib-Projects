#include "raylib.h"

int main(void) {
    InitWindow(800, 450, "Hello Raylib on Ubuntu!");
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("It works!", 350, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}