#include "sudooku.h"
int UNSOLVED =81;
int progress;
int main()
{
    int **puzzle;
    sudoku *sudoku;
    puzzle = createpuzzle();
    sudoku = Setyourpuzzle(puzzle);
    printPuzzle(sudoku->squares);
    while(UNSOLVED>0)
    {
        progress=checkyourpuzzle(sudoku->squares,sudoku->boxes);
        if(progress==0)
        {
            printf("failed nigga\n");
            break;
        }
    }
    printf("\n");
    printPuzzle(sudoku->squares);
    return 0;
}
