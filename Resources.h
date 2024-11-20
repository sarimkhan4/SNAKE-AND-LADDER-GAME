#include "raylib.h"
#include <stdio.h>

Font MyFont; // Font

Texture2D diceFaces[6]; // Dice images
Texture2D logoBackground; // Logo
Texture2D boardTexture; // New board texture for Snake and Ladder
Texture2D GameBackground; // Main backgrounf throughtout the game

void Load_Font() {
    MyFont = LoadFontEx("Resources/Fonts/myfont.ttf", 50, 0, 0); // Load font once
}

void Load_Resources (){
// Load texture with error handling
Texture2D LoadTextureWithCheck(const char *fileName) {
    Texture2D texture = LoadTexture(fileName);
    if (texture.width == 0 || texture.height == 0) {
        printf("Failed to load texture: %s\n", fileName);
    }
    return texture;
}
    // Load dice textures with error checking
    diceFaces[0] = LoadTextureWithCheck("Resources/dice_face_1.png");
    diceFaces[1] = LoadTextureWithCheck("Resources/dice_face_2.png");
    diceFaces[2] = LoadTextureWithCheck("Resources/dice_face_3.png");
    diceFaces[3] = LoadTextureWithCheck("Resources/dice_face_4.png");
    diceFaces[4] = LoadTextureWithCheck("Resources/dice_face_5.png");
    diceFaces[5] = LoadTextureWithCheck("Resources/dice_face_6.png");

    // Load background images with error checking
    logoBackground = LoadTextureWithCheck("Resources/logo.png");  // Logo
    boardTexture = LoadTextureWithCheck("Resources/board.png"); // Board background
    GameBackground = LoadTextureWithCheck("Resources/mainbackground.png"); // Whole Game Background
}

void Unload_Font() {
    UnloadFont(MyFont);  // Unload the font
}

// Unload all the resources
void Unload_Resources (){
    for (int i = 0; i < 6; i++) {
        UnloadTexture(diceFaces[i]);
    }
     UnloadTexture(logoBackground);
     UnloadTexture(GameBackground);
}