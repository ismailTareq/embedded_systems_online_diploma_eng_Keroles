#include <stdio.h>
#include <stdlib.h>
int main(void) {
	float a[2][2],b[2][2],c[2][2];
	int i,j;
	printf("enter the elements of first matrix\n");
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			printf("enter a[%d][%d]",i,j);
			scanf("%f",&a[i][j]);
		}
	}
	printf("enter the elements of second matrix\n");
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			printf("enter b[%d][%d]",i,j);
			scanf("%f",&b[i][j]);
		}
	}
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			c[i][j] = a[i][j] + b[i][j];
		}
	}
	printf("\n sum of matrix :");
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			printf("%.1f \t",c[i][j]);
			if(j==1)
				printf("\n");
		}
	}
	return EXIT_SUCCESS;
}

