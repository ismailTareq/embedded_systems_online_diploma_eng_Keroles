#include <stdio.h>
#include <ctype.h>
int main() {

 char str[1000];
    int char_counts[10] = { 0 };
    scanf("%s", str);
    for (int i = 0; str[i] != '\0'; i++) {
    if (isdigit(str[i])) {
      int digit_index = str[i] - '0';
      char_counts[digit_index]++;
    }
  }
    // Print digits array elements
    for (int i = 0; i < 10; i++) {
        printf("%d ", char_counts[i]);
    }
  return 0;
}
