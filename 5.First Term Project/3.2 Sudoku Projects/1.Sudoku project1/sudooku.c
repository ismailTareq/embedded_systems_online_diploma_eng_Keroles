#include "sudooku.h"
sudoku *createsudoku(square ***squares,Box **boxes)
{
    sudoku *Sudoku;
    Sudoku=(sudoku *)malloc(sizeof(Sudoku));
    Sudoku->squares = squares;
    Sudoku->boxes = boxes;
    return Sudoku;
}

sudoku *Setyourpuzzle(int **puzzle)
{
    square ***sudoku;
    Box **boxes;
    int i, j, x;
    int currentbox =0;

    sudoku = (square ***)malloc(sizeof(square **)*9);
    boxes = createpuzzleboxes();
    /* loop through rows */
    for (i = 0; i < 9; i++)
    {
        /* malloc space for each row */
        sudoku[i] = (square **)malloc(sizeof(square *)*9);

        /* loop through columns */
        for (j = 0; j < 9; j++)
        {
            /* malloc space for each square */
            sudoku[i][j] = (square *)malloc(sizeof(square));

            /* assign number to your sudoku */
            sudoku[i][j]->number = puzzle[i][j];

            /* assign row and column numbers to each square */
            sudoku[i][j]->row = i;
            sudoku[i][j]->column = j;
            sudoku[i][j]->solvable = 9;

            boxes[currentbox]->squares[boxes[currentbox]->numbers]=sudoku[i][j];
            sudoku[i][j]->box=boxes[currentbox];
            boxes[currentbox]->numbers++;

            for (x = 0; x < 9; x++)
            {
                sudoku[i][j]->possible[x] = 0;
            }

            if(j==2)
            {
                currentbox++;
            }
            if(j==5)
            {
                currentbox++;
            }
        }
        currentbox-=2;
        if(i==2)
            currentbox=3;
        if(i==5)
            currentbox=6;
    }

    /* loop through rows */
    for (i = 0; i < 9; i++)
    {
        /* loop through columns */
        for (j = 0; j < 9; j++)
        {
            if (sudoku[i][j]->number != 0)
            {
                sudoku[i][j]->solvable = 0;
                updateyoursudoku(sudoku, i, j);
                updateboxes(sudoku, i, j);
                UNSOLVED--;
            }
        }
    }
    return createsudoku(sudoku,boxes);
}

int updateyoursudoku(square ***sudoku,int i,int j)
{
    int k;
    int number = sudoku[i][j]->number;

    for (k=0;k<9;k++)
    {
        if (sudoku[k][j]->possible[number - 1] == 0)
        {
            sudoku[k][j]->solvable--;
        }
        sudoku[k][j]->possible[number -1] = 1;
    }

    for (k=0; k<9; k++)
    {
        if (sudoku[i][k]->possible[number - 1] == 0)
        {
            sudoku[i][k]->solvable--;
        }
        sudoku[i][k]->possible[number -1] = 1;
    }

    return 1;

}

int checkyourpuzzle(square ***sudoku,Box **boxes)
{
    int i,j;

    /* loop through rows */
    for (i = 0; i < 9; i++)
    {
        /* loop through columns */
        for (j = 0; j < 9; j++)
        {
            if (sudoku[i][j]->solvable == 1)
            {
                solvethissquare(sudoku[i][j]);
                updateyoursudoku(sudoku, i, j);
                updateboxes(sudoku, i, j);

            }
        }
    }

    if(singleboxcheck(sudoku,boxes))
        return 1;
    if (checkrows(sudoku,boxes))
        return 1;
    return checkcols(sudoku,boxes);
}

int **createpuzzle()
{
    int **puzzle;
    int i, j;
    int array[9][9]= {5, 3, 0,      0, 7, 0,     0, 0, 0,
                      6, 0, 0,      1, 9, 5,     0, 0, 0,
                      0, 9, 8,      0, 0, 0,     0, 6, 0,

                      8, 0, 0,      0, 6, 0,     0, 0, 3,
                      4, 0, 0,      8, 0, 3,     0, 0, 1,
                      7, 0, 0,      0, 2, 0,     0, 0, 6,

                      0, 6, 0,      0, 0, 0,     2, 8, 0,
                      0, 0, 0,      4, 1, 9,     0, 0, 5,
                      0, 0, 0,      0, 8, 0,     0, 7, 9 };



    puzzle = (int **)malloc(sizeof(int *)*9);

    for (i = 0; i < 9; i++)
    {
        puzzle[i] = (int *)malloc(sizeof(int)*9);

        for (j = 0; j < 9; j++)
        {
            puzzle[i][j] = array[i][j];
        }
    }

    return puzzle;
}

void printPuzzle(square ***puzzle)
{
    int i, j;

    printf("-------------------------------\n");
    for (i = 0; i < 9; i++)
    {
        printf("|");
        /* print each row */
        for (j = 0; j < 9; j++)
        {
            printf(" %d ", puzzle[i][j]->number);

            if (((j + 1) % 3) == 0)
            {
                printf("|");
            }
        }
        printf("\n");
        if (((i + 1) % 3) == 0)
        {
            printf("-------------------------------\n");
        }
    }
}
