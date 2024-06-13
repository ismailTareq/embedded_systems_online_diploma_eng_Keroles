#include "sudooku.h"
int checkrows(square ***sudoku,Box **boxes)
{
   int i,j,k;
   int sum[9];
   int place[9];
   for(i=0;i<9;i++)
   {
       for(j=0;j<9;j++)
       {
           sum[j]=0;
           place[j]=0;
       }
       for(j=0;j<9;j++)
       {
           if(sudoku[i][j]->number!=0)
            continue;

           for(k=0;k<9;k++)
           {
               if(sudoku[i][j]->possible[k]==0)
               {
                   sum[k]++;
                   place[k]=j;
               }
           }
       }
       for(k=0;k<9;k++)
       {
           if(sum[k]==1)
           {
               sudoku[i][place[k]]->number = k+1;
               sudoku[i][place[k]]->solvable=0;
               UNSOLVED--;
               updateyoursudoku(sudoku,i,place[k]);
               updateboxes(sudoku,i,place[k]);
               return 1;
           }
       }
   }
   return 0;
}


