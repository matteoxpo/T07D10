#include <stdio.h>
#include <stdlib.h>

int input(int **a, int *n);
void output(int *a, int n);
void swap(int *a, int i);
void sort(int *a, int n);

int main() {
  int *mas;
  int n;
  if (input(&mas, &n)) {
    sort(mas, n);
    output(mas, n);
    free(mas);
  } else {
    printf("n/a");
  }
  return 0;
}

int input(int **a, int *n) {
  char c = 0;
  int check = 1;
  if (scanf("%d", n)) {
    *a = (int *)malloc(*n * sizeof(int));
    for (int *p = *a; p - *a < *n; p++)
      if (scanf("%d%c", p, &c) && (c == ' ' || c == '\n' || c == EOF)) {
        continue;
      } else {
        check = 0;
        break;
      }
  } else {
    check = 0;
  }
  return check;
}

void output(int *a, int n) {
  for (int *p = a; p - a < n - 1; p++) printf("%d ", *p);
  printf("%d", *(a + n - 1));
}

void swap(int *a, int i) {
  int temp = *(a + i);
  *(a + i) = *(a + i + 1);
  *(a + i + 1) = temp;
}

void sort(int *a, int n) {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n - 1; j++)
      if (*(a + j) > *(a + j + 1)) swap(a, j);
}
