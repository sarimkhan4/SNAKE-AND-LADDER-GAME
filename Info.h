#define DICE_SIZE 100  // Dice display size remains 100x100
#define MIN_PLAYERS 2 // Minimum number of players 
#define MAX_PLAYERS 4 // Maximum number of players
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 700

// Screens Declaration
typedef enum { TITLE, PLAYER_SELECTION, INPUT, GAME, END } GameScreen;
GameScreen currentScreen = TITLE;

// Player Info
char playerNames[MAX_PLAYERS][20] = {""}; // Player names
int playerPositions[MAX_PLAYERS] = {0};   // Player positions
Color playerColors[MAX_PLAYERS] = {BLUE, YELLOW, GREEN, RED}; // Player colors
int currentPlayer = 0;
int numPlayers = MIN_PLAYERS; // Default to 2 players
int nameInputActive = 0;      // Index for which player's name is being entered

char rollingMessage[64] = ""; // To store rolling message
char S_L_Message[64] = "";    // To store snake and ladder check message
float S_L_MessageTime = 0.0f; // Timer for message duration
bool showS_L_Message = false; 

// Winner Info
char winnerName[20] = ""; // Winner name
bool gameOver = false; // Is game over?
float gameOverDelay = 0.0f; // For delay before transitioning to END_SCREEN
