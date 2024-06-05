#include <stdio.h>
#include <stdlib.h>
#define MY_DATA_MAX_SIZE  10
typedef unsigned int uint32;

uint32 My_Data[MY_DATA_MAX_SIZE] = {8, 1, 9, 5, 0, 7, 3, 2, 4, 6};
void Swap_Two_Numbers(uint32 *num1, uint32 *num2);
void Bubble_Sort(uint32 my_array[], uint32 array_length);
void Print_My_Data(uint32 my_array[], uint32 array_length);
int main()
{
    Print_My_Data(My_Data, MY_DATA_MAX_SIZE);
    Bubble_Sort(My_Data, MY_DATA_MAX_SIZE);
    Print_My_Data(My_Data, MY_DATA_MAX_SIZE);
    return 0;
}
void Swap_Two_Numbers(uint32 *num1, uint32 *num2)
{
    uint32 Temp_Number = *num1;
    *num1 = *num2;
    *num2 = Temp_Number;
}
void Bubble_Sort(uint32 my_array[], uint32 array_length)
{
    uint32 full_loop,array_loop;
    unsigned char flag=0;
    for(full_loop=0;full_loop<array_length-1;full_loop++)
    {
        for(array_loop=0;array_loop<array_length-1-full_loop;array_loop++)
        {
            if(my_array[array_loop]>my_array[array_loop+1])
            {
                Swap_Two_Numbers(&my_array[array_loop],&my_array[array_loop+1]);
                flag =1;
            }
        }
        if(flag ==0)
            return;
    }
}
void Print_My_Data(uint32 my_array[], uint32 array_length)
{
    uint32 Data_Counter = 0;
    for(Data_Counter=0; Data_Counter<array_length; Data_Counter++){
        printf("%i\t", my_array[Data_Counter]);
    }
    printf("\n");
}
