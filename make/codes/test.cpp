#include <stdio.h>

extern int add(int, int);
extern int sub(int, int);

int main() {
  printf("1 + 2 = %d\n", add(1, 2));
  printf("9 - 1 = %d\n", sub(9, 1));
}
