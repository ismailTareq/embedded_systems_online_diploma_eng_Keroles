#ifndef SUDOOKU_H_
#define SUDOOKU_H_
#include <stdio.h>
#include <stdlib.h>
extern int UNSOLVED;

typedef struct sudoku{
    struct square ***squares;
    struct Box **boxes;

}sudoku;

typedef struct Box{
    struct square **squares;
    int numbers;
    int possible[9];
    int solvable;
}Box;

typedef struct square{
    int number;
    int possible[9];
    int solvable;
    int row;
    int column;
    Box *box ;

}square;

int **createpuzzle();
void printPuzzle(square ***puzzle);
sudoku *Setyourpuzzle(int **puzzle);
sudoku *createsudoku(square ***squares,Box **boxes);
int updateyoursudoku(square ***sudoku,int i,int j);
int checkyourpuzzle(square ***sudoku,Box **boxes);
int solvethissquare(square *squares);


Box **createpuzzleboxes(void);
int updateboxes(square ***sudoku,int i,int j);
int singleboxcheck(square ***squares,Box **boxes);

#endif // SUDOOKU_H_
