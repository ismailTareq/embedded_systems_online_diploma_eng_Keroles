#include <stdio.h>

int main()
{
    int num1, num2;
    float f1, f2;

    // Get input
    scanf("%d %d", &num1, &num2);
    scanf("%f %f", &f1, &f2);

    printf("%d %d\n", num1 + num2, num1 - num2);
    printf("%.1f %.1f\n", f1 + f2, f1 - f2);

    return 0;
}
