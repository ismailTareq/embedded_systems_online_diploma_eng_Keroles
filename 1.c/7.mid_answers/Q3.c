#include<stdio.h>

void main()
{
	int n1 , n2 , i , flag;
	printf ("Please Enter Your Start point:");
	fflush (stdout);
	scanf  ("%d",&n1);
	printf ("Please Enter Your End point:");
	fflush (stdout);
	scanf  ("%d",&n2);

	printf("Prime numbers between %d and %d are: ", n1, n2);
	for (i = n1 + 1; i < n2; ++i) {

		// flag will be equal to 1 if i is prime
		flag = checkPrimeNumber(i);

		if (flag == 1) {
			printf("%d ", i);
		}
	}

}

int checkPrimeNumber(int n) {
	int j, flag = 1;

	for (j = 2; j <= n / 2; ++j)
	{

		if (n % j == 0)
		{
			flag = 0;
			break;
		}
	}

	return flag;
}
