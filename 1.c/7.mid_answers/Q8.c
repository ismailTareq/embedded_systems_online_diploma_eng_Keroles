#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void reverse(int num[],int size)
{
    int i,b[10];
    for(i=0;i<size;i++)
    {
        b[i]=num[size-1-i];
    }
    for(i=0;i<size;i++)
    {
        printf("%d",b[i]);
    }
}
int main()
{
    int arr[5]={1,2,3,4,5};
    int i;
    int size = sizeof(arr)/sizeof(&arr[0]);
    reverse(arr,size);

    return 0;
}
