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