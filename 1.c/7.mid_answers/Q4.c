#include<stdio.h>

int main()
{
	int arr [10] , x , i ;
	printf ("please choose your array size:");
	fflush (stdout);
	scanf ("%d",&x);
	printf ("please Enter your numbers: ");

	for (i=0 ; i <x ; i++)
	{
		fflush(stdout);
		scanf ("%d", &arr [i]);
	}
	arr [x]="\0";

	printf ("your numbers are: ");
	for (i=0 ; i<x ; i++)
	{
		printf ("%d \t", arr [i]);
	}
	printf ("\n");
	printf ("your reverse are: ");

	for (i = x-1 ; i >= 0; i--)
	{
		printf ("%d \t", arr[i]);
	}

return 0 ;
}

