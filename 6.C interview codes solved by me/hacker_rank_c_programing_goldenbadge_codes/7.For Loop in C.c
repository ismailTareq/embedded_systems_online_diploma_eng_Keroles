#include <stdio.h>

int main() {
    const char* word[] = { "one", "two", "three", "four", "five", "six", "seven",   "eight", "nine" };

  int a, b, i;
  scanf("%d\n%d", &a, &b);
    for (i = a; i <= b; i++) {
        if (i >= 1 && i <= 9) printf("%s\n", word[i - 1]);
        else if (i > 9 && i % 2 == 0) printf("even\n");
        else if (i > 9 && i % 2 == 1) printf("odd\n");
  }
  return 0;
}
