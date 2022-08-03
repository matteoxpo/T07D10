#include <stdio.h>
#include <stdlib.h>

#define ArrSize 100
void output_static(int a[][ArrSize], int n, int m);
int stat(int a[][ArrSize], int *n, int *m);

int input(int ***a, int n, int m);  // dynamic only
void output(int **a, int n, int m);
int dynamic_var1(int ***a, int *n, int *m);
int dynamic_var2(int ***a, int *n, int *m);
int dynamic_var3(int ***a, int *n, int *m, int *val_arr);

int symbolCorrect(char symbol);
int sizeCorrect(int s);
int main() {
  int staticMas[ArrSize][ArrSize];
  int **dynamicMas;
  int n = 0, m = 0;
  int command;
  int *val_arr = malloc(sizeof(int));
  if (scanf("%d", &command)) {
    switch (command) {
      case 1:
        if (stat(staticMas, &n, &m)) {
          output_static(staticMas, n, m);
        } else {
          printf("n/a");
        }
        break;
      case 2:
        if (dynamic_var1(&dynamicMas, &n, &m)) {
          output(dynamicMas, n, m);
          free(dynamicMas);
        } else {
          if (n != 0 && m != 0) {
            for (int i = 0; i < n; i++) free(dynamicMas[i]);
            free(dynamicMas);
          }
          printf("n/a");
        }
        break;
      case 3:
        if (dynamic_var2(&dynamicMas, &n, &m)) {
          output(dynamicMas, n, m);
          for (int i = 0; i < n; i++) free(dynamicMas[i]);
          free(dynamicMas);
        } else {
          if (n != 0 && m != 0) {
            for (int i = 0; i < n; i++) free(dynamicMas[i]);
            free(dynamicMas);
          }
          printf("n/a");
        }
        break;
      case 4:
        if (dynamic_var3(&dynamicMas, &n, &m, val_arr)) {
          output(dynamicMas, n, m);
          free(dynamicMas);
        } else {
          if (n != 0 && m != 0) {
            free(dynamicMas);
          }
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
int sizeCorrect(int s) { return s > 0 && s < ArrSize + 1 ? 1 : 0; }

void output_static(int a[][ArrSize], int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (j != n)
        printf("%d ", a[i][j]);
      else
        printf("%d", a[i][j]);
    }
    printf("\n");
  }
}
int stat(int a[][ArrSize], int *n, int *m) {
  char symbol;
  int check = 1;
  int el;
  if (scanf("%d %d%c", n, m, &symbol) == 3 && sizeCorrect(*n) &&
      sizeCorrect(*m) && symbolCorrect(symbol)) {
    for (int i = 0; i < *n; i++) {
      for (int j = 0; j < *m; j++) {
        if (scanf("%d%c", &el, &symbol) && symbolCorrect(symbol)) {
          a[i][j] = el;
        } else {
          check = 0;
          break;
        }
      }
    }
  } else {
    check = 0;
  }
  return check;
}

void output(int **a, int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%d ", a[i][j]);
    }
    printf("\n");
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
    (*a) = malloc(*n * *m * sizeof(int) + *m * sizeof(int *));
    int *p = (int *)(*a + *m);
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
    (*a) = malloc(*m * sizeof(int *));
    for (int i = 0; i < *n; i++) {
      (*a)[i] = malloc(*n * sizeof(int));
    }
    check = input(a, *n, *m);
  } else {
    check = 0;
  }
  return check;
}
int dynamic_var3(int ***a, int *n, int *m, int *val_arr) {
  char symbol;
  int check = 1;

  if (scanf("%d %d%c", n, m, &symbol) == 3 && sizeCorrect(*n) &&
      sizeCorrect(*m) && symbolCorrect(symbol)) {
    (*a) = malloc(*m * sizeof(int *));
    val_arr = malloc((*m) * (*n) * sizeof(int));
    for (int i = 0; i < *n; i++) (*a)[i] = val_arr + (*m) * i;
    check = input(a, *n, *m);

  } else {
    check = 0;
  }
  return check;
}