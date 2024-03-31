#include <stdio.h>
#include <stdbool.h>

#define N 9

// Function to print the solved Sudoku grid
void printGrid(int grid[N][N])
{
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
            printf("%2d", grid[row][col]);
        printf("\n");
    }
}

// Function to check if the assigned number is safe for the given row and column
bool isSafe(int grid[N][N], int row, int col, int num)
{
    // Check if the number is not already present in current row, current column, and current 3x3 subgrid
    for (int x = 0; x < N; x++)
        if (grid[row][x] == num || grid[x][col] == num)
            return false;

    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(int grid[N][N])
{
    int row, col;

    // If there are no unassigned positions, the puzzle is solved
    bool isComplete = true;
    for (row = 0; row < N && isComplete; row++)
        for (col = 0; col < N && isComplete; col++)
            if (grid[row][col] == 0)
                isComplete = false;

    if (isComplete)
        return true; // Puzzle solved

    // Find the first unassigned position
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == 0)
                goto found;

found:

    // Try assigning numbers 1 to 9
    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(grid, row, col, num))
        {
            grid[row][col] = num; // Assign the number if it's safe

            if (solveSudoku(grid)) // Recur to solve the rest of the puzzle
                return true;

            grid[row][col] = 0; // If the assignment doesn't lead to a solution, backtrack
        }
    }

    return false; // No solution exists
}

int main()
{
    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    if (solveSudoku(grid))
        printGrid(grid);
    else
        printf("No solution exists.");

    return 0;
}
