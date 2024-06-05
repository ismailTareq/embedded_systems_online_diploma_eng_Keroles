#include <stdio.h>
#include <stdlib.h>
#define DATA_MAX_SIZE     10
#define ELEMENT_NOT_FOUND -1
typedef unsigned int uint32;
typedef signed int sint32;
unsigned int My_Data[DATA_MAX_SIZE] = {11, 22, 33, 44, 55, 66, 77, 88 ,99 ,100};
sint32 LinearSearch(uint32 Data[], uint32 Data_Length, uint32 Req_Data);
int main()
{
    sint32 ret =0;
    ret = LinearSearch(My_Data, DATA_MAX_SIZE, 66);
    if(ret == ELEMENT_NOT_FOUND)
    {
         printf("Element is not found in your data !!\n");
    }
    else
    {
        printf("Element is found with index = %i \n", ret);
    }
    return 0;
}
uint32 LinearSearch(uint32 Data[], uint32 Data_Length, uint32 Req_Data)
{
    if(Data==NULL)
    {
        printf("no array being passed\n");
    }
    else
    {
        uint32 Index;

        for(Index = 0; Index < Data_Length; Index++)
        {
            if(Req_Data == Data[Index])
            {
                return Index;
            }
        }
        return -1;
    }
}
