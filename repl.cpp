#include <stdio.h>

int prompt(char* line) {
  int ret;
  printf("set-lang>");
  ret = scanf("%s", line);
  return ret;
}

int main() {
  char line[100];
  while(prompt(line) >= 0) {
    printf("%s\n", line);
  }
}
