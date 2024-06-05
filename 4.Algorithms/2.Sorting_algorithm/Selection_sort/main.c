#include <stdio.h>
#include <stdlib.h>
#define MY_DATA_MAX_SIZE  10
typedef unsigned int uint32;
uint32 My_Data[MY_DATA_MAX_SIZE] = {8, 1, 9, 5, 0, 7, 3, 2, 4, 6};
void Selection_Sort(uint32 my_array[], uint32 array_length);
void Swap_Two_Numbers(uint32 *num1, uint32 *num2);
void Print_My_Data(uint32 my_array[], uint32 array_length);
int main()
{
    Print_My_Data(My_Data, MY_DATA_MAX_SIZE);
    Selection_Sort(My_Data, MY_DATA_MAX_SIZE);
    Print_My_Data(My_Data, MY_DATA_MAX_SIZE);
    return 0;
}
void Selection_Sort(uint32 my_array[], uint32 array_length)
{
    uint32 iterator1;
    uint32 minimum_index;
    uint32 iterator2;
    for(iterator1=0;iterator1<array_length-1;iterator1++)
    {
        minimum_index = iterator1;
        for(iterator2=iterator1+1;iterator2<array_length;iterator2++)
        {
            if(my_array[iterator2]<my_array[minimum_index])
            {
                minimum_index = iterator2;
            }
        }
        Swap_Two_Numbers(&my_array[minimum_index],&my_array[iterator1]);
    }
}
void Swap_Two_Numbers(uint32 *num1, uint32 *num2)
{
    unsigned int Temp_Number = *num1;
    *num1 = *num2;
    *num2 = Temp_Number;
}
void Print_My_Data(uint32 my_array[], uint32 array_length)
{
    unsigned int Data_Counter = 0;
    for(Data_Counter=0; Data_Counter<array_length; Data_Counter++){
        printf("%i\t", my_array[Data_Counter]);
    }
    printf("\n");
}
