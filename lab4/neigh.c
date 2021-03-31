#include <stdio.h>
#include <stdlib.h>

int main()
{
  int n;
  int r;
  scanf("%d %d", &n, &r);

  int N = n + r * 2;

  int (*t)[N] = calloc(N * N, sizeof(**t));

  for (int y = r; y < N - r; ++y)
    for (int x = r; x < N - r; ++x)
      scanf("%d", &t[y][x]);

  int left_sum = 0;
  for (int y = 0; y < 2 * r; ++y)
    for (int x = 0; x < 2 * r; ++x)
      left_sum += t[y][x];

  for (int y = r; y < N - r; ++y)
  {
    for (int x = 0; x < 2 * r; ++x)
      left_sum += t[y + r][x];

    int sum = left_sum;

    for (int x = r; x < N - r; ++x)
    {
      for (int y2 = y - r; y2 <= y + r; ++y2)
        sum += t[y2][x + r];

      printf("%d ", sum);

      for (int y2 = y - r; y2 <= y + r; ++y2)
        sum -= t[y2][x - r];
    }

    printf("\n");

    for (int x = 0; x < 2 * r; ++x)
      left_sum -= t[y - r][x];
  }

  free(t);

  return 0;
}

