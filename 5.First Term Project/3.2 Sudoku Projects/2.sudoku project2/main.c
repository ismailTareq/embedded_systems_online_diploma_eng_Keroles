#include <stdio.h>
#include <stdbool.h>

#define N 9

bool findEmptyLocation(int grid[N][N], int* row, int* col) {
    for (*row = 0; *row < N; (*row)++) {
        for (*col = 0; *col < N; (*col)++) {
            if (grid[*row][*col] == 0) {
                return true;
            }
        }
    }
    return false;
}

bool usedInRow(int grid[N][N], int row, int num) {
    for (int col = 0; col < N; col++) {
        if (grid[row][col] == num) {
            return true;
        }
    }
    return false;
}

bool usedInCol(int grid[N][N], int col, int num) {
    for (int row = 0; row < N; row++) {
        if (grid[row][col] == num) {
            return true;
        }
    }
    return false;
}

bool usedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (grid[row + boxStartRow][col + boxStartCol] == num) {
                return true;
            }
        }
    }
    return false;
}

bool isSafe(int grid[N][N], int row, int col, int num) {
    return !usedInRow(grid, row, num) &&
           !usedInCol(grid, col, num) &&
           !usedInBox(grid, row - row % 3, col - col % 3, num);
}

bool solveSudoku(int grid[N][N]) {
    int row, col;
    if (!findEmptyLocation(grid, &row, &col)) {
        return true;
    }
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid)) {
                return true;
            }
            grid[row][col] = 0;
        }
    }
    return false;
}

void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            printf("%d ", grid[row][col]);
        }
        printf("\n");
    }
}

int main() {
     int array[9][9]= {4, 0, 0,      6, 0, 0,     0, 0, 5,
                      0, 0, 7,      0, 0, 2,     0, 0, 0,
                      0, 9, 0,      0, 1, 0,     0, 4, 0,

                      0, 0, 0,      1, 6, 9,     8, 0, 0,
                      0, 0, 0,      0, 0, 0,     0, 0, 0,
                      0, 2, 1,      0, 0, 0,     9, 0, 0,

                      0, 0, 0,      0, 0, 0,     3, 0, 0,
                      6, 0, 0,      5, 8, 0,     2, 0, 0,
                      0, 5, 0,      0, 9, 3,     0, 0, 0 };


    if (solveSudoku(array) == true) {
        printf("The solution to the given Sudoku puzzle is:\n");
        printGrid(array);
    } else {
        printf("No solution exists for the given Sudoku puzzle.\n");
    }
    return 0;
}
