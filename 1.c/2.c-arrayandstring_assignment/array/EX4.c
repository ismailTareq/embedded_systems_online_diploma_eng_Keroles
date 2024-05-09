#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[20],num,i,loc,x;
    printf("enter number of elements:\n");
    scanf("%d",&num);

    for(i=0;i<num;i++)
    {
        scanf("%d",&a[i]);
    }
    printf("enter the elements u  want to insert:\n");
    scanf("%d",&x);
    printf("enter the location:\n");
    scanf("%d",&loc);
    num++;
    for(i=num;i>=loc;i--)
    {
        a[i]=a[i-1];
    }

    a[loc-1]= x;
    for(i=0;i<num;i++)
    {
        printf("%d \t",a[i]);
    }
    return 0;
}
