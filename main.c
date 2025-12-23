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
    // First, set all cells to empty
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            maze[i][j] = EMPTY;
        }
    }
    
    // Add walls to create the maze pattern
    // Top-left region walls
    for (int i = 1; i <= 3; i++) maze[i][3] = WALL;
    for (int j = 1; j <= 3; j++) maze[3][j] = WALL;
    
    // Top-center walls
    for (int i = 1; i <= 3; i++) maze[i][7] = WALL;
    for (int i = 1; i <= 3; i++) maze[i][8] = WALL;
    
    // Top-right region walls
    for (int i = 1; i <= 3; i++) maze[i][12] = WALL;
    for (int j = 12; j <= 14; j++) maze[3][j] = WALL;
    
    // Middle-left walls
    for (int i = 5; i <= 7; i++) maze[i][3] = WALL;
    for (int j = 1; j <= 3; j++) maze[7][j] = WALL;
    
    // Middle-center vertical barrier
    for (int i = 5; i <= 10; i++) maze[i][7] = WALL;
    for (int i = 5; i <= 10; i++) maze[i][8] = WALL;
    
    // Middle-right walls
    for (int i = 5; i <= 7; i++) maze[i][12] = WALL;
    for (int j = 12; j <= 14; j++) maze[7][j] = WALL;
    
    // Bottom-left region walls
    for (int i = 12; i <= 14; i++) maze[i][3] = WALL;
    for (int j = 1; j <= 3; j++) maze[12][j] = WALL;
    
    // Bottom-center walls
    for (int i = 12; i <= 14; i++) maze[i][7] = WALL;
    for (int i = 12; i <= 14; i++) maze[i][8] = WALL;
    
    // Bottom-right region walls
    for (int i = 12; i <= 14; i++) maze[i][12] = WALL;
    for (int j = 12; j <= 14; j++) maze[12][j] = WALL;
    
    // Additional horizontal connectors
    for (int j = 5; j <= 6; j++) maze[5][j] = WALL;
    for (int j = 9; j <= 10; j++) maze[5][j] = WALL;
    
    for (int j = 5; j <= 6; j++) maze[10][j] = WALL;
    for (int j = 9; j <= 10; j++) maze[10][j] = WALL;
    
    // Set escape point
    maze[ESCAPE_ROW][ESCAPE_COL] = ESCAPE;
    
    // Initialize last police position
    last_police_pos.row = -1;
    last_police_pos.col = -1;
}

// The Manhattan distance between two positions
int manhattan_distance(Position p1, Position p2) {
    return abs(p1.row - p2.row) + abs(p1.col - p2.col);
}

// Check if a move is valid (within bounds and not a wall)
bool is_valid_move(int row, int col) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        return false;
    }
    if (maze[row][col] == WALL) {
        return false;
    }
    return true;
}

// Place thief and policeman randomly with distance constraints
void place_entities() {
    Position escape_pos = {ESCAPE_ROW, ESCAPE_COL};
    bool valid_placement = false;
    
    while (!valid_placement) {
        // Randomly place thief
        thief_pos.row = rand() % SIZE;
        thief_pos.col = rand() % SIZE;
        
        // Check if thief position is valid
        if (maze[thief_pos.row][thief_pos.col] != EMPTY) {
            continue;
        }
        
        // Check distance from thief to escape point
        if (manhattan_distance(thief_pos, escape_pos) < MIN_DISTANCE) {
            continue;
        }
        
        // Randomly place policeman
        police_pos.row = rand() % SIZE;
        police_pos.col = rand() % SIZE;
        
        // Check if policeman position is valid
        if (maze[police_pos.row][police_pos.col] != EMPTY) {
            continue;
        }
        
        // Check distance between thief and policeman
        if (manhattan_distance(thief_pos, police_pos) >= MIN_DISTANCE) {
            valid_placement = true;
        }
    }
    
    // Mark positions in maze
    maze[thief_pos.row][thief_pos.col] = THIEF;
    maze[police_pos.row][police_pos.col] = POLICEMAN;
}

// Draw the maze to the screen
void draw_maze() {
    system("clear");
    
    printf("\n  Maze Chase Game - %s Mode\n", difficulty == 1 ? "Easy" : "Hard");
    printf("  T = Thief (You)  |  P = Policeman  |  E = Escape Point\n\n");
    
    // Top border
    printf("    ");
    for (int j = 0; j < SIZE; j++) {
        printf("+---");
    }
    printf("+\n");
    
    // Maze content with cell boundaries
    for (int i = 0; i < SIZE; i++) {
        // Row number
        printf(" %2d ", i + 1);
        
        // Cell content
        for (int j = 0; j < SIZE; j++) {
            printf("|");
            if (i == thief_pos.row && j == thief_pos.col) {
                printf(" T ");
            } else if (i == police_pos.row && j == police_pos.col) {
                printf(" P ");
            } else if (maze[i][j] == WALL) {
                printf(" W ");
            } else if (i == ESCAPE_ROW && j == ESCAPE_COL) {
                printf(" E ");
            } else {
                printf("   ");
            }
        }
        printf("|\n");
        
        // Horizontal line after each row
        printf("    ");
        for (int j = 0; j < SIZE; j++) {
            printf("+---");
        }
        printf("+\n");
    }
    
    // Column numbers
    printf("    ");
    for (int j = 0; j < SIZE; j++) {
        printf("  %2d", j + 1);
    }
    printf("\n\n");
}

// Get player's move
void get_player_move() {
    char move;
    bool valid = false;
    
    while (!valid) {
        printf("Your move (W=up, S=down, A=left, D=right): ");
        scanf(" %c", &move);
        
        int new_row = thief_pos.row;
        int new_col = thief_pos.col;
        
        switch (move) {
            case 'w':
            case 'W':
                new_row--;
                break;
            case 's':
            case 'S':
                new_row++;
                break;
            case 'a':
            case 'A':
                new_col--;
                break;
            case 'd':
            case 'D':
                new_col++;
                break;
            default:
                printf("Invalid input! Use W, A, S, or D.\n");
                continue;
        }
        
        if (is_valid_move(new_row, new_col)) {
            // Update maze
            maze[thief_pos.row][thief_pos.col] = EMPTY;
            if (new_row == ESCAPE_ROW && new_col == ESCAPE_COL) {
                maze[new_row][new_col] = ESCAPE;
            }
            thief_pos.row = new_row;
            thief_pos.col = new_col;
            valid = true;
        } else {
            printf("Invalid move! You cannot go through walls or out of bounds.\n");
        }
    }
}

// Computer move for easy mode (random)
void computer_move_easy() {
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int valid_moves[4][2];
    int count = 0;
    
    // Find all valid moves
    for (int i = 0; i < 4; i++) {
        int new_row = police_pos.row + directions[i][0];
        int new_col = police_pos.col + directions[i][1];
        
        if (is_valid_move(new_row, new_col)) {
            valid_moves[count][0] = new_row;
            valid_moves[count][1] = new_col;
            count++;
        }
    }
    
    // Pick a random valid move
    if (count > 0) {
        int choice = rand() % count;
        maze[police_pos.row][police_pos.col] = EMPTY;
        police_pos.row = valid_moves[choice][0];
        police_pos.col = valid_moves[choice][1];
    }
}

// Computer move for hard mode (optimal pathfinding)
void computer_move_hard() {
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int best_moves[4][2];
    int best_count = 0;
    int min_distance = SIZE * SIZE;
    
    // Save current position for loop prevention
    Position current = police_pos;
    
    // Find all moves with minimum distance to thief
    for (int i = 0; i < 4; i++) {
        int new_row = police_pos.row + directions[i][0];
        int new_col = police_pos.col + directions[i][1];
        
        if (is_valid_move(new_row, new_col)) {
            // Avoid going back to last position (prevent loops)
            if (new_row == last_police_pos.row && new_col == last_police_pos.col) {
                continue;
            }
            
            Position new_pos = {new_row, new_col};
            int dist = manhattan_distance(new_pos, thief_pos);
            
            if (dist < min_distance) {
                min_distance = dist;
                best_count = 0;
                best_moves[best_count][0] = new_row;
                best_moves[best_count][1] = new_col;
                best_count++;
            } else if (dist == min_distance) {
                best_moves[best_count][0] = new_row;
                best_moves[best_count][1] = new_col;
                best_count++;
            }
        }
    }
    
    // If no moves avoid the last position, allow any valid move
    if (best_count == 0) {
        for (int i = 0; i < 4; i++) {
            int new_row = police_pos.row + directions[i][0];
            int new_col = police_pos.col + directions[i][1];
            
            if (is_valid_move(new_row, new_col)) {
                Position new_pos = {new_row, new_col};
                int dist = manhattan_distance(new_pos, thief_pos);
                
                if (dist <= min_distance) {
                    best_moves[best_count][0] = new_row;
                    best_moves[best_count][1] = new_col;
                    best_count++;
                }
            }
        }
    }
    
    // Pick a random move among the best moves
    if (best_count > 0) {
        int choice = rand() % best_count;
        maze[police_pos.row][police_pos.col] = EMPTY;
        last_police_pos = current;
        police_pos.row = best_moves[choice][0];
        police_pos.col = best_moves[choice][1];
    }
}

// Check if player won
bool check_win() {
    return (thief_pos.row == ESCAPE_ROW && thief_pos.col == ESCAPE_COL);
}

// Check if player lost
bool check_lose() {
    return (thief_pos.row == police_pos.row && thief_pos.col == police_pos.col);
}

// Get difficulty level from user
int get_difficulty() {
    int choice;
    printf("\n=== Maze Chase Game ===\n");
    printf("Select difficulty level:\n");
    printf("1. Easy (Random policeman moves)\n");
    printf("2. Hard (Smart policeman)\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);
    
    while (choice != 1 && choice != 2) {
        printf("Invalid choice! Enter 1 or 2: ");
        scanf("%d", &choice);
    }
    
    return choice;
}

// Ask if player wants to play again
bool play_again() {
    char choice;
    printf("\nDo you want to play again? (Y/N): ");
    scanf(" %c", &choice);
    return (choice == 'Y' || choice == 'y');
}

// Main game loop
void play_game() {
    // Get difficulty
    difficulty = get_difficulty();
    
    // Initialize maze
    initialize_maze();
    place_entities();
    
    // Game loop
    bool game_over = false;
    while (!game_over) {
        draw_maze();
        
        // Player's turn
        get_player_move();
        
        // Check win condition
        if (check_win()) {
            draw_maze();
            printf("\nYou won! You escaped!\n");
            game_over = true;
            continue;
        }
        
        // Check lose condition after player move
        if (check_lose()) {
            draw_maze();
            printf("\nYou lost! The policeman caught you!\n");
            game_over = true;
            continue;
        }
        
        // Computer's turn
        if (difficulty == 1) {
            computer_move_easy();
        } else {
            computer_move_hard();
        }
        
        // Check lose condition after computer move
        if (check_lose()) {
            draw_maze();
            printf("\nYou lost! The policeman caught you!\n");
            game_over = true;
        }
    }
}

// Main function
int main() {
    // Seed random number generator
    srand(time(NULL));
    
    // Game loop
    do {
        play_game();
    } while (play_again());
    
    printf("\nThank you for playing! Goodbye!\n\n");
    
    return 0;
}