#include <stdio.h>
// Function to check snake or a ladder
int checkSnakeOrLadder(int position) {
   // Snakes and ladders
    int snakes[] = {17, 54, 62, 64, 87, 93, 95, 98};
    int snakeTail[] = {7, 34, 19, 60, 24, 73, 75, 79};
    int ladders[] = {1, 4, 9, 21, 28, 51, 71, 80};
    int ladderTop[] = {38, 14, 31, 42, 84, 67, 91, 100};
    for (int i = 0; i < 8; i++) {
        if (position == snakes[i]) {
            snprintf(S_L_Message, sizeof(S_L_Message), "OPPS!, %s LANDED ON A SNAKE!", playerNames[currentPlayer]);
            showS_L_Message = true;
            S_L_MessageTime = 5.0f; // Time for message to stay on screen
            return snakeTail[i];
        }
    }
    for (int i = 0; i < 8; i++) {
        if (position == ladders[i]){
            snprintf(S_L_Message, sizeof(S_L_Message), "YAYY!, %s CLIMBED A LADDER!", playerNames[currentPlayer]);
            showS_L_Message = true;
            S_L_MessageTime = 5.0f; // Time for message to stay on screen
            return ladderTop[i];
        }
    }
    return position;
}