#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[20],num,element,i;
    int found;
    printf("enter number of elements:\n");
    scanf("%d",&num);

    for(i=0;i<num;i++)
    {
        scanf("%d",&a[i]);
    }
    printf("the element to be searched is:\n");
    scanf("%d",&element);
    for(i=0;i<num;i++)
    {
        if(element==a[i])
        {
            found =1;
            break;
        }
    }
    if(found ==1)
    {
        printf("the element is found at location %d",i+1);
    }
    else
    {
        printf("the element is not found");
    }

    return 0;
}
