#include <stdio.h>
#include <stdlib.h>

#define ArrSize 100

int input(int ***a, int n, int m);  // dynamic only
void output(int **a, int n, int m);

int dynamic_var1(int ***a, int *n, int *m);
int dynamic_var2(int ***a, int *n, int *m);
int dynamic_var3(int ***a, int *n, int *m, int **val_arr);

void matrix_sort(int **a, int n, int m);
void swap(int **a, int i, int j);
int sum(int **a, int i, int m);

int symbolCorrect(char symbol);
int sizeCorrect(int s);

int main() {
  int **dynamicMas;
  int n = 0, m = 0;
  int command;
  int *val_arr;
  if (scanf("%d", &command)) {
    switch (command) {
      case 1:
        if (dynamic_var1(&dynamicMas, &n, &m)) {
          matrix_sort(dynamicMas, n, m);
          output(dynamicMas, n, m);
          free(dynamicMas);
        } else {
          if (n != 0 && m != 0) free(dynamicMas);
          printf("n/a");
        }
        break;
      case 2:
        if (dynamic_var2(&dynamicMas, &n, &m)) {
          matrix_sort(dynamicMas, n, m);
          output(dynamicMas, n, m);

          for (int i = 0; i < n; i++) free(dynamicMas[i]);
          free(dynamicMas);

        } else {
          if (n != 0 && m != 0) free(dynamicMas);
          printf("n/a");
        }
        break;
      case 3:
        if (dynamic_var3(&dynamicMas, &n, &m, &val_arr)) {
          matrix_sort(dynamicMas, n, m);
          output(dynamicMas, n, m);
          free(dynamicMas);
          free(val_arr);
        } else {
          if (n != 0 && m != 0) free(dynamicMas);
          printf("n/a");
        }
        break;
      default:
        printf("n/a");
        break;
    }
  } else {
    printf("n/a");
  }

  return 0;
}
int symbolCorrect(char symbol) {
  return symbol == ' ' || symbol == '\n' || symbol == EOF ? 1 : 0;
}
int sizeCorrect(int s) { return s > 0 ? 1 : 0; }

void output(int **a, int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (j != m - 1)
        printf("%d ", a[i][j]);
      else
        printf("%d", a[i][j]);
    }
    if (i != n - 1) printf("\n");
  }
}
int input(int ***a, int n, int m) {
  char symbol;
  int el;
  int check = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (scanf("%d%c", &el, &symbol) == 2 && symbolCorrect(symbol)) {
        (*a)[i][j] = el;
      } else {
        check = 0;
        break;
      }
    }
  }
  return check;
}

int dynamic_var1(int ***a, int *n, int *m) {
  char symbol;
  int check = 1;
  if (scanf("%d %d%c", n, m, &symbol) == 3 && sizeCorrect(*n) &&
      sizeCorrect(*m) && symbolCorrect(symbol)) {
    (*a) = malloc((*n) * (*m) * sizeof(int) + (*m) * sizeof(int *));
    int *p = (int *)((*a) + *n);
    for (int i = 0; i < *n; i++) {
      (*a)[i] = p + *m * i;
    }
    check = input(a, *n, *m);
  } else {
    check = 0;
  }
  return check;
}
int dynamic_var2(int ***a, int *n, int *m) {
  char symbol;
  int check = 1;

  if (scanf("%d %d%c", n, m, &symbol) == 3 && sizeCorrect(*n) &&
      sizeCorrect(*m) && symbolCorrect(symbol)) {
    (*a) = malloc(*n * sizeof(int *));
    for (int i = 0; i < *n; i++) {
      (*a)[i] = malloc(*m * sizeof(int));
    }
    check = input(a, *n, *m);
  } else {
    check = 0;
  }
  return check;
}
int dynamic_var3(int ***a, int *n, int *m, int **val_arr) {
  char symbol;
  int check = 1;

  if (scanf("%d %d%c", n, m, &symbol) == 3 && sizeCorrect(*n) &&
      sizeCorrect(*m) && symbolCorrect(symbol)) {
    (*a) = malloc(*n * sizeof(int *));
    (*val_arr) = malloc((*m) * (*n) * sizeof(int));
    for (int i = 0; i < *n; i++) (*a)[i] = *val_arr + (*m) * i;
    check = input(a, *n, *m);

  } else {
    check = 0;
  }
  return check;
}

void matrix_sort(int **a, int n, int m) {
  int min = sum(a, 0, m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (sum(a, j, m) > sum(a, i, m)) swap(a, i, j);
    }
  }
}

void swap(int **a, int i, int j) {
  int *temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}
int sum(int **a, int i, int m) {
  int s = 0;
  for (int j = 0; j < m; j++) {
    s += a[i][j];
  }
  return s;
}
