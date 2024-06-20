#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    char s[100];  // Assuming the maximum length of the input string is 100 characters

    printf("Hello, World!\n");
    fgets(s, sizeof(s), stdin);  // Read the input string from stdin

    printf("%s", s);  // Print the input string

    return 0;
}
