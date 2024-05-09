#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[10][10],y[10][10];
    int r,c,i,j;
    printf("enter rows and the columns of matrix:\n");
    scanf("%d %d",&r,&c);

    printf("enter elements of matrix :\n");
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            printf("enter elements a[%d][%d] :",i+1,j+1);
            scanf("%d",&a[i][j]);
        }
    }
    printf("the entered matrix :\n");
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            printf("%d \t",a[i][j]);
            if(j==c-1)
            {
                printf("\n");
            }
        }
    }
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            y[j][i] = a[i][j];
        }
    }
    printf("the transpose matrix :\n");
    for(i=0;i<c;i++)
    {
        for(j=0;j<r;j++)
        {
            printf("%d \t",y[i][j]);
            if(j==r-1)
            {
                printf("\n");
            }
        }
    }
    return 0;
}
