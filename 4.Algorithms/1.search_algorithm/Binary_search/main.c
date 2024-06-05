#include <stdio.h>
#include <stdlib.h>
#define DATA_MAX_SIZE     10

typedef unsigned int uint32;
typedef signed int sint32;

uint32 MyData[DATA_MAX_SIZE] = {0, 11, 22, 33, 44, 55, 66, 77, 88, 99};
uint32 BinarySearch(uint32 Data[], uint32 start, uint32 end, uint32 Req_Value);

int main()
{
    uint32 Ret = 0;

    Ret = BinarySearch(MyData, 0, DATA_MAX_SIZE-1, 22);
    printf("Ret = %i \n", Ret);
    Ret = BinarySearch(MyData, 0, DATA_MAX_SIZE-1, 77);
    printf("Ret = %i \n", Ret);
    Ret = BinarySearch(MyData, 0, DATA_MAX_SIZE-1, 100);
    printf("Ret = %i \n", Ret);
    return 0;
}
uint32 BinarySearch(uint32 Data[], uint32 start, uint32 end, uint32 Req_Value)
{
    uint32 middle =0;

    while(start<=end)
    {
        middle = start + ((end-start)/2);
        if(Req_Value == Data[middle])
            return middle;
        else if (Req_Value > Data[middle])
            start = middle + 1;
        else if (Req_Value < Data[middle])
            end = middle - 1;
    }
    return 1;
}
