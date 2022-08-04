#include <stdio.h>
#include <stdlib.h>

#define ArrSize 100

int input(int ***a, int n, int m);  // dynamic only
void output(int **a, int n, int m);

int dynamic_var(int ***a, int *n, int *m);
void dynamic(int ***a, int n, int m);

int sum(int **a, int **b, int n, int m, int ***res);
int mul(int **a, int **b, int n1, int m1, int n2, int m2, int ***res);
int transp(int **a, int n, int m, int ***res);
int symbolCorrect(char symbol);
int sizeCorrect(int s);

int main() {
  int **dynamicMas1;
  int **dynamicMas2;
  int n1 = 0, m1 = 0;
  int n2 = 0, m2 = 0;
  int command;
  int **res;
  if (scanf("%d", &command)) {
    switch (command) {
      case 1:
        if (dynamic_var(&dynamicMas1, &n1, &m1) &&
            dynamic_var(&dynamicMas2, &n2, &m2)) {
          if (n1 == n2 && m1 == m2) {
            sum(dynamicMas1, dynamicMas2, n1, m1, &res);
            output(res, n1, m1);
            for (int i = 0; i < n1; i++) free(res[i]);
            free(res);
          } else {
            printf("n/a");
          }
          for (int i = 0; i < n1; i++) free(dynamicMas1[i]);
          free(dynamicMas1);
          for (int i = 0; i < n2; i++) free(dynamicMas2[i]);
          free(dynamicMas2);
        } else {
          if (n1 != 0 && m1 != 0) free(dynamicMas1);
          if (n2 != 0 && m2 != 0) free(dynamicMas2);
          printf("n/a");
        }
        break;
      case 2:
        if (dynamic_var(&dynamicMas1, &n1, &m1) &&
            dynamic_var(&dynamicMas2, &n2, &m2)) {
          if (mul(dynamicMas1, dynamicMas2, n1, m1, n2, m2, &res)) {
            output(res, n1, m2);
            for (int i = 0; i < n1; i++) free(res[i]);
            free(res);
          }

          for (int i = 0; i < n1; i++) free(dynamicMas1[i]);
          free(dynamicMas1);
          for (int i = 0; i < n2; i++) free(dynamicMas2[i]);
          free(dynamicMas2);
        } else {
          if (n1 != 0 && m1 != 0) free(dynamicMas1);
          if (n2 != 0 && m2 != 0) free(dynamicMas2);
          printf("n/a");
        }
        break;
      case 3:
        if (dynamic_var(&dynamicMas1, &n1, &m1)) {
          transp(dynamicMas1, n1, m1, &res);
          output(res, m1, n1);
          for (int i = 0; i < m1; i++) free(res[i]);
          free(res);
          for (int i = 0; i < n1; i++) free(dynamicMas1[i]);
          free(dynamicMas1);
        } else {
          if (n1 != 0 && m1 != 0) free(dynamicMas1);
          printf("n/a");
        }
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
int dynamic_var(int ***a, int *n, int *m) {
  char symbol;
  int check = 1;

  if (scanf("%d %d%c", n, m, &symbol) == 3 && sizeCorrect(*n) &&
      sizeCorrect(*m) && symbolCorrect(symbol)) {
    dynamic(a, *n, *m);
    check = input(a, *n, *m);
  } else {
    check = 0;
  }
  return check;
}

void dynamic(int ***a, int n, int m) {
  (*a) = malloc(n * sizeof(int *));
  for (int i = 0; i < n; i++) (*a)[i] = malloc(m * sizeof(int));
}

int sum(int **a, int **b, int n, int m, int ***res) {
  dynamic(res, n, m);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      (*res)[i][j] = 0;
      (*res)[i][j] += (a[i][j] + b[i][j]);
    }
  return 1;
}

int mul(int **a, int **b, int n1, int m1, int n2, int m2, int ***res) {
  int check = 1;
  dynamic(res, n1, m2);
  if (m1 != n2) {
    check = 0;
  } else {
    for (int i = 0; i < n1; i++) {
      for (int j = 0; j < m2; j++) {
        (*res)[i][j] = 0;
        for (int k = 0; k < n2; k++) {
          (*res)[i][j] += a[i][k] * b[k][j];
        }
      }
    }
  }
  return check;
}

int transp(int **a, int n, int m, int ***res) {
  int check = 1;
  dynamic(res, m, n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      (*res)[j][i] = a[i][j];
    }
  }
  return 1;
}
