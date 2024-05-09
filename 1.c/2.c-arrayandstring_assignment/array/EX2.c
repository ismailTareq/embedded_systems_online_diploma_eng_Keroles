#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float num[100],sum =0.0,average;
	int i,n;
	printf("enter the no of data:\n");
	scanf("%d",&n);
	while(n>100||n<=0)
    {
        printf("error!plz enter number range from 1 to 100 \n");
        printf(" enter the no of data again :\n");
        scanf("%d",&n);
    }
	for(i=0;i<n;i++)
	{
		printf("%d enter number: ",i+1);
		scanf("%f",&num[i]);
		sum+=num[i];
	}
	average=sum/n;
	printf("Average = %.2f",average);
	return EXIT_SUCCESS;
}

