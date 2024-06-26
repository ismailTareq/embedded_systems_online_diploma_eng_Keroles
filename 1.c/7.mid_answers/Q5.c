#include<stdio.h>

int main()
{
	int num, counter = 0;
	printf ("Please Enter an int num: ");
	fflush (stdout);
	scanf ("%d",&num);

	while ( num > 0)
	{

		// If current bit is 1
		if (num & 1) {
			counter++;
		}
		num = num >> 1;

	}
	printf("number of 1's is: %d ",counter);
	return 0;
}
