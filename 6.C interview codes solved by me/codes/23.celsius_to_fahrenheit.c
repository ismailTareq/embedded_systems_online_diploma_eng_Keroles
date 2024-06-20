#include <stdio.h>
#include <stdlib.h>
#include "math.h"



int main()
{
    float celsius, fahrenheit;
    printf("Program to convert Temperature from Celsius to Fahrenheit\n");
    printf("Enter temperature in Celsius: ");
    scanf("%f", &celsius);
    fahrenheit = (celsius * 9 / 5) + 32;
    printf("%.2f Celsius = %.2f Fahrenheit", celsius, fahrenheit);
    return 0;
}
