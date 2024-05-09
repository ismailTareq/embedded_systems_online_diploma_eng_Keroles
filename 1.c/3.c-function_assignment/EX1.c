#include <stdio.h>
#include <stdlib.h>

void printPrimes(int num1, int num2)
{
    printf("prime number between %d to %d are: ", num1, num2);

    while(num1 <= num2)
    {
        if(isPrime(num1))
        {
            printf("%d, ", num1);
        }
        num1++;
    }
}
int isPrime(int num)
{
    int i;
    for(i=2; i<=num/2; i++)
    {
        if(num % i == 0)
        {
            return 0;
        }
    }
    return 1;
}
int main()
{
    int num1, num2;
    printf("Enter the two numbers: ");
    scanf("%d %d", &num1, &num2);
    printPrimes(num1, num2);

    return 0;
}


