#include <stdio.h>
#include <stdlib.h>
#include "math.h"



int main()
{
    int year;
    printf("Program to find given year is leap or not\n");
    printf("Please Enter a year: ");
    scanf("%d", &year);
    if (year % 400 == 0) {
      printf("Given year %d is a leap year.", year);
    }
    else if (year % 100 == 0) {
      printf("Given year %d is not a leap year.", year);
    }
    else if (year % 4 == 0) {
      printf("Given year %d is a leap year.", year);
    }
    else {
      printf("Given year %d is not a leap year.", year);
    }
    return 0;
}
