#include "raylib.h"
#include "Info.h"
#include "Snake_Ladder.h"
#include <stdio.h>
#include <stdlib.h>


// Dice variables
Vector2 dicePosition = { SCREEN_WIDTH - DICE_SIZE - 35.0f, 200.0f }; // Dice position at 100x100 size
int diceValue = 1;            // Final dice face
bool isRolling = false;       // Is dice rolling?
float rollingTime = 0.0f;     // Time spent rolling
float angle = 0.0f;           // Rotation angle for animation

// Function to roll the dice
int rollDice() {
    return (rand() % 6) + 1;
}

// Start dice rolling animation
void StartDiceRolling() {
    isRolling = true;
    rollingTime = 0.0f;
    angle = 0.0f;
}

// Update dice rolling
void UpdateDiceRolling(float deltaTime) {
    if (isRolling) {
        rollingTime += deltaTime;
        if (rollingTime < 1.0f) {
            angle += 30.0f;  // Rotate dice during rolling
            if (angle >= 360.0f) {
                angle = 0.0f;
            } 
            diceValue = rollDice();  // Change dice face
        } else {
            isRolling = false;
            diceValue = rollDice();
            playerPositions[currentPlayer] += diceValue;
            // Update player position and check for snake or ladder
            playerPositions[currentPlayer] = checkSnakeOrLadder(playerPositions[currentPlayer]);
            // To check if anyone reached position 100
            if (playerPositions[currentPlayer] >= 100) {
                snprintf(winnerName, sizeof(winnerName), "%s", playerNames[currentPlayer]);
                gameOver = true;  // Flag to indicate game is over
                gameOverDelay = 1.0f;  // 1 second delay before moving to end screen
            }
            // Rolling message printing
            snprintf(rollingMessage, sizeof(rollingMessage), "%s ROLLED A %d! NOW AT POSITION %d", 
                     playerNames[currentPlayer], diceValue, playerPositions[currentPlayer]);
            // Next player turn update
            currentPlayer = (currentPlayer + 1) % numPlayers;
        }
    }
    if (showS_L_Message) {
        S_L_MessageTime -= deltaTime;
        if (S_L_MessageTime <= 0.0f) {
            showS_L_Message = false; // Hide the message after the timeout
        }
    }
        if (gameOver) {
            gameOverDelay -= deltaTime;
            if (gameOverDelay <= 0.0f) {
            currentScreen = END;  // Transition to the END_SCREEN after delay
            }
        }
}

// Draw the dice with text prompt
void DrawDice() {
    // Display Current turn message
    DrawTextEx(MyFont, TextFormat("CURRENT TURN : %s", playerNames[currentPlayer]), (Vector2) {750, 70}, 30, 1.0f, BLACK);
    // Display prompt above the dice
    DrawTextEx(MyFont, "CLICK ON DICE TO ROLL", (Vector2) {750, 120}, 30, 5.0f, BLACK);

    // Draw the dice with rotation if rolling, else draw normally
    if (isRolling) {
        DrawTexturePro(diceFaces[0],
            (Rectangle){0, 0, diceFaces[0].width, diceFaces[0].height},
            (Rectangle){dicePosition.x - 100, dicePosition.y + 20, DICE_SIZE, DICE_SIZE},
            (Vector2){DICE_SIZE / 2.0f, DICE_SIZE / 2.0f}, angle, WHITE);
            
    } else {
        DrawTexturePro(diceFaces[diceValue - 1],
            (Rectangle){0, 0, diceFaces[diceValue - 1].width, diceFaces[diceValue - 1].height},
            (Rectangle){dicePosition.x - 100, dicePosition.y + 20, DICE_SIZE, DICE_SIZE},
            (Vector2){DICE_SIZE / 2.0f, DICE_SIZE / 2.0f}, 0.0f, WHITE);
              
        DrawTextEx(MyFont, rollingMessage, (Vector2) {750, 330}, 18, 1.0f, BLACK);

        if (showS_L_Message) {
            DrawTextEx(MyFont, S_L_Message, (Vector2) {775, 300}, 18, 1.0f, RED);
        }
    }
}

// Check if the dice is clicked and start rolling if clicked
void CheckDiceClick() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !isRolling) {
        // Get the mouse position
        Vector2 mousePosition = GetMousePosition();

        // Check if the mouse click is within the dice bounds
        Rectangle diceBounds = {dicePosition.x - 150, dicePosition.y - 30, DICE_SIZE, DICE_SIZE};
        if (CheckCollisionPointRec(mousePosition, diceBounds)) {
            StartDiceRolling();
        }
    }
}


