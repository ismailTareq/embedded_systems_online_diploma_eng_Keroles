#include <stdio.h>

void sum(int *a, int *b) {
    int sum = *a + *b;
    int diff = abs(*a - *b);
    *a = sum;
    *b = diff;
}

int main() {
    int a, b,*p1,*p2;
    scanf("%d\n%d", &a, &b);
    p1 = &a;
    p2 = &b;
    sum(p1, p2);
    printf("%d\n%d", a, b);

    return 0;
}
