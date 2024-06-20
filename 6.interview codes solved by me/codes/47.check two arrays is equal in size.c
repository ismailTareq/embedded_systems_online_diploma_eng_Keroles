#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
#include <ctype.h>



int main()
{
    int arr1[]={1,2,5,3,4,5};
    int arr2[]={2,3,1,9,5};
    int size1=sizeof(arr1)/sizeof(arr1[0]);
    int size2=sizeof(arr2)/sizeof(arr2[0]);
    if(size1 == size2){
        printf("size of both arrays are equal");
    }else{
        printf("size of arrays are not equal");
    }
    return 0;
}
