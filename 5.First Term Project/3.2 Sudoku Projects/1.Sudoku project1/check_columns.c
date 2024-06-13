#include "sudooku.h"
int checkcols(square ***sudoku, Box **boxes) {
  int i, j, k;
  int sum[9];
  int place[9];
  for (j = 0; j < 9; j++) {
    for (i = 0; i < 9; i++) {
      sum[i] = 0;
      place[i] = 0;
    }
    for (i = 0; i < 9; i++) {
      if (sudoku[i][j]->number != 0) continue;
      for (k = 0; k < 9; k++) {
        if (sudoku[i][j]->possible[k] == 0) {
          sum[k]++;
          place[k] = i;
        }
      }
    }
    for (k = 0; k < 9; k++) {
      if (sum[k] == 1) {
        sudoku[place[k]][j]->number = k + 1;
        sudoku[place[k]][j]->solvable = 0;
        UNSOLVED--;
        updateyoursudoku(sudoku, place[k], j);
        updateboxes(sudoku, place[k], j);
        return 1;
      }
    }
  }
  return 0;
}
