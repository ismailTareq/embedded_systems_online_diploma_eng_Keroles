#include <stdio.h>
#include <stdlib.h>
#define MY_DATA_MAX_SIZE  10
typedef unsigned int uint32;
uint32 My_Data[MY_DATA_MAX_SIZE] = {8, 1, 9, 5, 0, 7, 3, 2, 4, 6};

void Insertion_Sort(uint32 my_array[], uint32 array_length);
void Print_My_Data(uint32 my_array[], uint32 array_length);
int main()
{
    Print_My_Data(My_Data, MY_DATA_MAX_SIZE);
    Insertion_Sort(My_Data, MY_DATA_MAX_SIZE);
    Print_My_Data(My_Data, MY_DATA_MAX_SIZE);
    return 0;
}
void Insertion_Sort(uint32 my_array[], uint32 array_length)
{
    uint32 Iteration,key;
    int compare;
    for(Iteration=1;Iteration<array_length;Iteration++)
    {
        key = my_array[Iteration];
        compare = Iteration-1;
        while(key<my_array[compare]&&compare>=0)
        {
            my_array[compare+1]=my_array[compare];
            compare--;
        }
         my_array[compare+1]=key;
    }
}
void Print_My_Data(uint32 my_array[], uint32 array_length){
    uint32 Data_Counter = 0;
    for(Data_Counter=0; Data_Counter<array_length; Data_Counter++){
        printf("%i\t", my_array[Data_Counter]);
    }
    printf("\n");
}
