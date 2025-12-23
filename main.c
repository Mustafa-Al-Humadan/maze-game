#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 16
#define ESCAPE_ROW 7  // 8th row (0-indexed is 7)
#define ESCAPE_COL 15 // 16th column (0-indexed is 15)
#define MIN_DISTANCE 16

// Cell types
#define EMPTY 0
#define WALL 1
#define THIEF 2
#define POLICEMAN 3
#define ESCAPE 4

// Structure to hold positions
typedef struct {
    int row;
    int col;
} Position;

// Global variables
int maze[SIZE][SIZE];
Position thief_pos;
Position police_pos;
Position last_police_pos;
int difficulty; // 1 for easy, 2 for hard

// Function prototypes
void initialize_maze();
void draw_maze();
int manhattan_distance(Position p1, Position p2);
bool is_valid_move(int row, int col);
void place_entities();
void get_player_move();
void computer_move_easy();
void computer_move_hard();
bool check_win();
bool check_lose();
void play_game();
int get_difficulty();
bool play_again();

// Initialize the maze with walls
void initialize_maze() {
    // First, we set all cells to empty
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            maze[i][j] = EMPTY;
        }
    }
    
    // Add walls to create the maze pattern
    // Horizontal walls
    for (int j = 2; j < 7; j++) maze[2][j] = WALL;
    for (int j = 9; j < 14; j++) maze[2][j] = WALL;
    
    for (int j = 2; j < 7; j++) maze[5][j] = WALL;
    for (int j = 9; j < 14; j++) maze[5][j] = WALL;
    
    for (int j = 2; j < 7; j++) maze[8][j] = WALL;
    for (int j = 9; j < 14; j++) maze[8][j] = WALL;
    
    for (int j = 2; j < 7; j++) maze[11][j] = WALL;
    for (int j = 9; j < 14; j++) maze[11][j] = WALL;
    
    for (int j = 2; j < 7; j++) maze[13][j] = WALL;
    for (int j = 9; j < 14; j++) maze[13][j] = WALL;
    
    // Vertical walls
    for (int i = 2; i < 14; i++) maze[i][7] = WALL;
    
    // Set escape point
    maze[ESCAPE_ROW][ESCAPE_COL] = ESCAPE;
    
    // Initialize last police position
    last_police_pos.row = -1;
    last_police_pos.col = -1;
}