#include "raylib.h"
#include <stdio.h>
// Draw Players on Board according to the board image 
void DrawPlayersOnBoard() {
    int cellWidth = 60;    // Cell width based on the board image
    int cellHeight = 63;   // Cell height based on the board image
    int boardStartX = 130; // X offset to align with the board image
    int boardStartY = 28;  // Y offset to align with the board image 
// Loops to check and then draw the players on board    
    for (int p = 0; p < numPlayers; p++) {
        int position = playerPositions[p];
        if (position < 0) {
            position = 0; // Ensure before start players are at 0
        }      
        int row = (position - 1) / 10;
        int col = (position - 1) % 10;
        // Adjust for zigzag pattern, reverse column order on odd rows
        if (row % 2 == 1) {
            col = 10 - 1 - col;
        }
        // Calculate X and Y coordinates based on the adjusted cell size
        int x = boardStartX + col * cellWidth + cellWidth / 2;
        int y = boardStartY + (10 - 1 - row) * cellHeight + cellHeight / 2;
        // Draw the player marker (small colored circle)
        DrawCircle(x, y, 10, playerColors[p]);
    }
}
