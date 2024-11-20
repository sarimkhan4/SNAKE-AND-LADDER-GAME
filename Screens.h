#include "raylib.h"
#include "Resources.h"
#include "Dice.h"
#include "Players.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// First Screen to display
void TITLE_SCREEN (){
    DrawTexture(logoBackground, 20, 20, WHITE); // LOGO
    DrawTextEx(MyFont, "WELCOME TO SNAKE & LADDER",(Vector2) {130, 200}, 60, 2.0f,  BLACK);
    DrawTextEx(MyFont,"PRESENTED BY :", (Vector2) {330, 320}, 40, 2.0f, BLACK);
    DrawTextEx(MyFont,"ELITE GAMERZ", (Vector2) {650, 380}, 50, 2.0f, BLACK);
    DrawTextEx(MyFont," Press ENTER to start",(Vector2) {385, 600}, 40, 1.0f, BLACK);
    if (IsKeyPressed(KEY_ENTER)) {
        currentScreen = PLAYER_SELECTION;
    }            
}

// Second Screen to display
void PLAYER_SELECTION_SCREEN (){
    DrawTexture(logoBackground, 20, 20, WHITE); // LOGO
    DrawTextEx(MyFont, "SELECT NUMBER OF PLAYERS (2-4):", (Vector2) {190, 180}, 50, 2.0f, DARKBLUE);
    DrawTextEx(MyFont, TextFormat("PLAYERS: %d", numPlayers), (Vector2) {460, 300}, 50, 2.0f, BLACK);
    DrawTextEx(MyFont, "PRESS UP / DOWN TO CHANGE", (Vector2) {260, 430}, 45, 2.0f, DARKBLUE);
    DrawTextEx(MyFont, "Press ENTER to Confirm", (Vector2) {370, 600}, 40, 1.0f, BLACK);

    if (IsKeyPressed(KEY_UP)) {
        numPlayers = (numPlayers < MAX_PLAYERS) ? numPlayers + 1 : MAX_PLAYERS;
    } else if (IsKeyPressed(KEY_DOWN)) {
        numPlayers = (numPlayers > MIN_PLAYERS) ? numPlayers - 1 : MIN_PLAYERS;
    } else if (IsKeyPressed(KEY_ENTER)) {
        currentScreen = INPUT;
        nameInputActive = 0;
    }
} 

// Third Screen to display
void INPUT_SCREEN (){
    DrawTexture(logoBackground, 20, 20, WHITE); // LOGO
    DrawTextEx(MyFont, TextFormat("ENTER PLAYERS NAME %d :", nameInputActive + 1), (Vector2) {285, 180}, 50, 3.0f, BLACK);
    DrawTextEx (MyFont, "(MAX 8 CHARACTERS)", (Vector2) {380, 240}, 40, 2.0f, BLACK);
    DrawTextEx(MyFont, playerNames[nameInputActive], (Vector2) {470, 310}, 60, 2.0f, DARKBLUE);
    DrawTextEx(MyFont, "Press ENTER to Confirm Name", (Vector2) {310, 600}, 40, 1.0f, BLACK);

    int key = GetCharPressed();
    while (key > 0 && strlen(playerNames[nameInputActive]) < 8) {
        playerNames[nameInputActive][strlen(playerNames[nameInputActive]) + 1] = '\0';
        playerNames[nameInputActive][strlen(playerNames[nameInputActive])] = (char)key;
        key = GetCharPressed();
    }
        if (IsKeyPressed(KEY_BACKSPACE) && strlen(playerNames[nameInputActive]) > 0) {
            playerNames[nameInputActive][strlen(playerNames[nameInputActive]) - 1] = '\0';
        }
        if (IsKeyPressed(KEY_ENTER)) {
            nameInputActive++;
                if (nameInputActive >= numPlayers) {
                    currentScreen = GAME;
                }
        }       
}

// Fourth Screen to display
void GAME_SCREEN (float deltaTime){
    DrawTexture(boardTexture, 120, 40, WHITE); // Draw the board background

    // Players identification info
    DrawCircle(875, 480, 10, BLUE);
    DrawTextEx(MyFont, TextFormat("= PLAYER : 1"), (Vector2) {900, 470}, 20, 2.0f, BLACK);
    DrawCircle(875, 530, 10, YELLOW);
    DrawTextEx(MyFont, TextFormat("= PLAYER : 2"), (Vector2) {900, 520}, 20, 2.0f, BLACK);
    DrawCircle(875, 580, 10, GREEN);
    DrawTextEx(MyFont, TextFormat("= PLAYER : 3"), (Vector2) {900, 570}, 20, 2.0f, BLACK);
    DrawCircle(875, 630, 10, RED);
    DrawTextEx(MyFont, TextFormat("= PLAYER : 4"), (Vector2) {900, 620}, 20, 2.0f, BLACK);
    DrawRectangleLinesEx((Rectangle){850, 450, 210, 200}, 5, BLACK); // Box around colours representation for each player
            
    // Draw the players on the board
    DrawPlayersOnBoard();

    // Draw the dice and handle rolling
    DrawDice();

    // Only roll dice if clicked on it
    CheckDiceClick(); 

    // Update dice rollig when clicked 
    UpdateDiceRolling(deltaTime); 
}

// Fifth and last Screen to display
void END_SCREEN (){
    DrawTexture(logoBackground, 20, 20, WHITE); // LOGO
    DrawTextEx(MyFont, "CONGRATULATIONS!", (Vector2) {300, 200}, 60, 4.0f, BLACK);
    DrawTextEx(MyFont, TextFormat("WINNER: %s", winnerName), (Vector2) {350, 300}, 50, 2.0f, GREEN);
    DrawTextEx(MyFont, "Press ENTER to play again or ESC to exit", (Vector2) {250, 600}, 40, 1.0f, BLACK);

    if (IsKeyPressed(KEY_ENTER)) {
    // Reset the game to start over
        currentScreen = TITLE;
        gameOver = false;
        memset(playerPositions, 0, sizeof(playerPositions));  // Reset player positions    
    }
}
    
