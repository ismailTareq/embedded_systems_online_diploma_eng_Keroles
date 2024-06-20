#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
#include <ctype.h>
void print_non_repeating(char str[]) {
  char char_counts[256] = {0};
  for (int i = 0; str[i] != '\0'; i++)
  {
    char_counts[str[i]]++;
    if (char_counts[str[i]] == 1)
    {
      printf("%c", str[i]);
    }
  }
}

int main() {
  char str[100];

  printf("Enter a string: ");
  gets(str);
  printf("Non-repeating characters: ");
  print_non_repeating(str);

  return 0;
}
