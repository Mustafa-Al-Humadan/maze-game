The maze game
---
Description
Maze Chase is a terminal-based strategy game where you play as a thief trying to escape through a 16x16 grid maze while being pursued by a policeman. The game features:

* Two difficulty levels (Easy and Hard)

* Strategic wall placements creating challenging pathways

* Turn-based gameplay

* Smart AI pathfinding in Hard mode

* Distance-based random placement system
---
Prerequisites
To compile and run this game, you need:
For Linux/Mac:

* GCC Compiler (usually pre-installed)

  * Check if installed: gcc --version

  * Install on Ubuntu/Debian: sudo apt-get install gcc

  * Install on Mac: xcode-select --install

For Windows:

* MinGW-w64 or GCC via WSL

  * Option 1 - MinGW: Download from MinGW-w64

  * Option 2 - WSL: Install Ubuntu from Microsoft Store, then install GCC
---
Installation & Compilation
Step 1: Download the Files
Make sure you have these files in the same directory:

* main.c (the source code)

* README (this file)

Step 2: Open Terminal/Command Prompt
Navigate to the directory containing the files:

```bash
cd path/to/your/game/folder
```

Step 3: Compile the Code
On Linux/Mac:

```bash
gcc -o maze_game main.c -std=c99
```

On Windows (MinGW):

```bash
gcc -o maze_game.exe main.c -std=c99
```

On Windows (WSL):

```bash
gcc -o maze_game main.c -std=c99
```

Optional - Compile with all warnings enabled (recommended for debugging):

```bash
gcc -o maze_game main.c -std=c99 -Wall -Wextra
```

Expected Output:
If compilation is successful, you'll see no errors and a new executable file will be created:

* Linux/Mac: maze_game

* Windows: maze_game.exe
---
Running the Game
On Linux/Mac/WSL:

```bash
./maze_game
```

On Windows (MinGW):

```bash
maze_game.exe
```

Or simply double-click the executable file.
---
How to Play
Starting the Game

1. Select Difficulty Level:

   ```
   === Maze Chase Game ===
   Select difficulty level:
   1. Easy (Random policeman moves)
   2. Hard (Smart policeman)
   Enter your choice (1 or 2):
   ```

   * Type 1 for Easy mode (policeman moves randomly)

   * Type 2 for Hard mode (policeman chases you intelligently)

2. The Maze Appears:

   ```
     +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
   1 |   |   |   | W |   |   |   |   |   |   |   |   |   |   |   |   |
     +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
   ...
   ```

3. Control Your Thief:

   ```
   Your move (W=up, S=down, A=left, D=right):
   ```

   Movement Controls:

   * W or w - Move UP (↑)

   * S or s - Move DOWN (↓)

   * A or a - Move LEFT (←)

   * D or d - Move RIGHT (→)

   Press Enter after typing your move.
---
Game Symbols
Symbol Meaning T Thief (You) P Policeman (Computer) W Wall (Cannot pass through) E Escape Point (Your goal!) Empty cell Safe to move
Game Rules
Objective
WIN: Reach the Escape Point E (located at row 8, column 16)\
LOSE: Get caught by the Policeman P
Movement Rules

* ✅ Move one cell at a time (up, down, left, or right)

* ❌ NO diagonal moves allowed

* ❌ Cannot move through walls W

* ❌ Cannot move outside the grid boundaries

* 🔄 Game is turn-based: You move → Policeman moves → You move → ...
---
Difficulty Modes
Easy Mode (1):

* Policeman moves randomly to any adjacent valid cell

* Good for beginners and learning the maze layout

Hard Mode (2):

* Policeman uses intelligent pathfinding

* Always moves closer to you (using Manhattan distance)

* Avoids infinite loops by not returning to previous position

* Very challenging! Requires strategic planning

Initial Placement

* Thief and Policeman are placed randomly

* Minimum 16 squares apart (Manhattan distance)

* Thief starts at least 16 squares from Escape Point

* Ensures fair gameplay with time to plan your route
---
Troubleshooting
Problem: Screen doesn't clear between moves
Solution for Windows users: Open main.c and replace:

```c
system("clear");
```

with:

```c
system("cls");
```

Then recompile.
Problem: Compilation errors about undefined functions
Solution: Make sure you're using C99 standard or later:

```bash
gcc -o maze_game main.c -std=c99
```

Problem: "gcc: command not found"
Solution:

* Linux: sudo apt-get install build-essential

* Mac: xcode-select --install

* Windows: Install MinGW or use WSL (see Prerequisites)

Problem: Warning about implicit declaration
Solution: Add -std=c99 flag to compilation command.
Problem: Executable permission denied (Linux/Mac)
Solution:

```bash
chmod +x maze_game
./maze_game
```

Problem: Game runs too slowly
Solution: This is normal on some terminals. The game refreshes the screen after each move.
Technical Details
Algorithm Details
Easy Mode:

* Random selection from all valid adjacent cells

* Time Complexity: O(1)

---

Hard Mode:

* Manhattan distance calculation: |x₂ - x₁| + |y₂ - y₁|

* Finds all adjacent cells with minimum distance to thief

* Randomly selects among optimal moves

* Loop prevention: Avoids returning to previous position

* Time Complexity: O(1) per move

Distance Constraints

* Manhattan Distance is used for all distance calculations

* Minimum initial distance (Thief ↔️ Policeman): 16 squares

* Minimum initial distance (Thief ↔️ Escape): 16 squares

* These ensure fair gameplay and strategic depth

Maze Dimensions

* Grid Size: 16×16 cells

* Total Cells: 256

* Wall Distribution: Strategic placement creating corridors

* Escape Point: Fixed at (Row 8, Column 16)

Code Structure

* Language: C (C99 standard)

* Libraries: stdio.h, stdlib.h, time.h, stdbool.h

* Functions: Modular design with clear separation of concerns

* Comments: Comprehensive inline documentation

Playing Tips
Strategy for Easy Mode:

* Learn the maze layout

* Plan a direct route to the Escape Point

* Policeman's random moves give you time

Strategy for Hard Mode:

* Use walls as barriers

* Create distance before making escape run

* Corner the policeman behind walls

* Think 3-4 moves ahead

* The policeman takes the shortest path—use this against it!

Advanced Technique:

* Lead the policeman to one side of the maze

* Circle around through corridors

* Make your final escape run when policeman is trapped

If you encounter any issues not covered in the Troubleshooting section:

1. Verify all prerequisites are installed

2. Check that main.c is complete and unmodified

3. Ensure you're using GCC with C99 support

4. Try compiling with verbose output: gcc -o maze_game main.c -std=c99 -v

Good luck escaping the maze!