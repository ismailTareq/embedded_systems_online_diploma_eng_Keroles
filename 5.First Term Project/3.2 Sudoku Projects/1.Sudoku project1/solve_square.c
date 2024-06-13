#include "sudooku.h"
int solvethissquare(square *squares)
{
    int k;
    for(k=0;k<9;k++)
    {
        if(squares->possible[k]==0)
        {
            squares->number=k+1;
            squares->solvable=0;
            UNSOLVED--;
        }
    }
}
