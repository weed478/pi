#include <stdio.h>
#include <stdlib.h>

int main()
{
  int n;
  scanf("%d", &n);

  int *t = malloc(n * n * sizeof(*t));

  int **rows = malloc(n * sizeof(*rows));
  for (int y = 0; y < n; ++y)
    rows[y] = t + n * y;

  for (int i = 0; i < n * n; ++i)
      scanf("%d", t + i);

  int *last_value = 0;
  for (;;)
  {
    int **max_row = 0;
    for (int y = 0; y < n; ++y)
      if (rows[y] < t + y * n + n && (max_row == 0 || rows[y][0] < **max_row))
        max_row = rows + y;

    if (max_row == 0)
      break;

    if (last_value == 0 || **max_row != *last_value)
      printf("%d ", **max_row);
    last_value = *max_row;
    ++*max_row;
  }

  printf("\n");

  free(t);
  free(rows);

  return 0;
}

