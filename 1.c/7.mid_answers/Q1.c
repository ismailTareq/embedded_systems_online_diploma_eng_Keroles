
#include <stdio.h>

int fun (int);

int main ()
{
	unsigned int num;
	printf ("Please Enter a Number: ");
	fflush (stdout);
	scanf("%d",&num);
	printf ("%d",fun(num));
}

int fun (int num)
{
	unsigned int y;
	static unsigned  int sum = 0;

	if (num != 0)
	{
		y = num % 10;
		sum = sum + y;
		fun (num/10);
	}
	else
	{
		return 0;
	}
	return sum;
}
