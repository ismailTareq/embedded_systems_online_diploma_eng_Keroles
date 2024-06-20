#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,n,sum=0;
    scanf("%i",&n);
    int *arr =(int *)malloc(sizeof(int)*n);
    for(i=0;i<n;i++)
    {
        scanf("%i",&arr[i]);
        sum+=arr[i];
    }
    printf("%i",sum);
    return 0;
}
