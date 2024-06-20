#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
#include <ctype.h>

void print_non_repeating(char str[]) {
  int char_counts[256] = {0};
  for (int i = 0; str[i] != '\0'; i++) {
    char_counts[str[i]]++;
  }
  for (int i = 0; i < 256; i++) {
    if (char_counts[i] == 1) {
      printf("%c ",(char)i);
    }
  }
  printf("\n");
}

int main() {
  char str[100];
  printf("Enter a string: ");
  gets(str);
  printf("Non-repeating characters: ");
  print_non_repeating(str);
  return 0;
}
