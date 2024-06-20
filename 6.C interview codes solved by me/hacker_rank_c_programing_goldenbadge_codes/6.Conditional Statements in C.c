#include <stdio.h>

int main() {
  int n;
  scanf("%i",&n);
  if(1 <= n && n <= 9)
  {
      const char *numbers[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
      printf("%s \n",numbers[n-1]);
  }
  else {
  printf("Greater than 9");
  }

  return 0;
}
