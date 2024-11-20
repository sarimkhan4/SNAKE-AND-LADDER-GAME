#include "raylib.h"
#include "Screens.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake and Ladder Game");
    srand(time(0)); 
    SetTargetFPS(60);

    Load_Font (); // Font Loaded
    Load_Resources (); // Load all resources

    while (!WindowShouldClose()) {

        float deltaTime = GetFrameTime();

        BeginDrawing();

        ClearBackground(WHITE);
        
        DrawTexture (GameBackground, 0, 0, WHITE); // Whole game background 

        switch (currentScreen) { // Draw the background based on current screen
        
            case TITLE : {
                TITLE_SCREEN ();
                break;
            }

            case PLAYER_SELECTION : {
                PLAYER_SELECTION_SCREEN ();
                break;
            }

            case INPUT : {
                INPUT_SCREEN ();
                break;
            }

            case GAME : {
                GAME_SCREEN (deltaTime);
                break;
            }

            case END : {
                END_SCREEN ();
                break;
            }
        }

        EndDrawing();

    }

    Unload_Resources (); // Unload all resources

    Unload_Font(); // Unload the font
     
    CloseWindow();

    return 0;
}
