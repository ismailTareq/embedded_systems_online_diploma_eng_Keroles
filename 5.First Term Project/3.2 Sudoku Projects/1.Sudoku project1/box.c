#include "sudooku.h"
int singleboxcheck(square ***squares,Box **boxes)
{
    int i,j,k;
    int count,temp;
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            count =0;
            for(k=0;k<9;k++)
            {
                if(boxes[i]->squares[k]->number!=0)
                    continue;

                if(boxes[i]->squares[k]->possible[j]==0)
                {
                    count++;
                    temp =k;
                }
                if(count==2)
                    break;
            }
            if(count==1)
            {
                boxes[i]->squares[temp]->number = j+1;
                UNSOLVED--;
                boxes[i]->squares[temp]->solvable=0;
                updateyoursudoku(squares,boxes[i]->squares[temp]->row,boxes[i]->squares[temp]->column);
                return 1;
            }
        }
    }
    return 0;
}

Box **createpuzzleboxes(void)
{
    int i,j;
    Box **boxes;
    boxes = (Box **)malloc(sizeof(Box *)*9);
    for(i=0;i<9;i++)
    {
        boxes[i]= (Box *)malloc(sizeof(Box));
        boxes[i]->squares=(square **)malloc(sizeof(square *)*9);
        boxes[i]->numbers=0;
        boxes[i]->solvable=9;
        for(j=0;j<9;j++)
        {
            boxes[i]->possible[j]=0;
        }
    }
    return boxes;
}
int updateboxes(square ***sudoku,int i,int j)
{
    int k;
    int number = sudoku[i][j]->number;
    Box *box;
    box =sudoku[i][j]->box;
    for(k=0;k<9;k++)
    {
        if(box->squares[k]->possible[number-1]==0)
        {
            box->squares[k]->solvable--;
        }
        box->squares[k]->possible[number-1]=1;
    }
}
