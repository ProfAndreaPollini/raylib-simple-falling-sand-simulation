#include <vector>

#include "raylib.h"


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define CELL_SIZE 5
#define GRID_WIDTH (SCREEN_WIDTH / CELL_SIZE)
#define GRID_HEIGHT (SCREEN_HEIGHT / CELL_SIZE)

void DrawWorld(const std::vector<bool> &world) {
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (world[y * GRID_WIDTH + x]) {
                DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, LIGHTGRAY);
            }
        }
    }
}
void UpdateWorld(std::vector<bool>& world)
{
    for (int y = GRID_HEIGHT - 1; y >= 0; y--)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            if (world[y * GRID_WIDTH + x])
            {
                if (y < GRID_HEIGHT - 1)
                {
                    if (!world[(y + 1) * GRID_WIDTH + x])
                    {
                        world[y * GRID_WIDTH + x] = false;
                        world[(y + 1) * GRID_WIDTH + x] = true;
                    }
                    else
                    {
                        int dx = GetRandomValue(-1, 1);
                        if (x + dx >= 0 && x + dx < GRID_WIDTH && !world[(y + 1) * GRID_WIDTH + x + dx])
                        {
                            world[y * GRID_WIDTH + x] = false;
                            world[(y + 1) * GRID_WIDTH + x + dx] = true;
                        }
                    }
                }
            }
        }
    }
}

void AddSand(std::vector<bool> &world, int mouseX, int mouseY) {
    int x = mouseX / CELL_SIZE;
    int y = mouseY / CELL_SIZE;

    if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
        world[y * GRID_WIDTH + x] = true;
    }
}

int main() {
    std::vector<bool> world(GRID_WIDTH * GRID_HEIGHT, false);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Falling Sand Simulation");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            AddSand(world, GetMouseX(), GetMouseY());
        }
        UpdateWorld(world);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawWorld(world);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
