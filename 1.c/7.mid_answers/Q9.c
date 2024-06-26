#include <stdio.h>


	int maxConsecutiveOnes(int x)
	{
	    int count = 0;

	    while (x!=0)
	    {
	        x = (x & (x << 1));

	        count++;
	    }

	    return count;
	}

	int main()
	{
		int x;
		printf ("Enter an int number: ");
		fflush (stdout);
		scanf ("%d",&x);
	    printf ( "%d",maxConsecutiveOnes(x)) ;
	    return 0;
	}


