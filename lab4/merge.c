#include <stdio.h>
#include <stdlib.h>

int parent(int i)
{
  return (i - 1) / 2;
}

int left(int i)
{
  return 2 * i + 1;
}

int right(int i)
{
  return 2 * i + 2;
}

void heapify(int *A[], int n, int i)
{
  int m = i;
  do
  {
    i = m;
    int l = left(m);
    int r = right(m);

    if (l < n && *A[l] < *A[m])
      m = l;

    if (r < n && *A[r] < *A[m])
      m = r;

    int *tmp = A[i];
    A[i] = A[m];
    A[m] = tmp;
  } while (m != i);
}

void build_heap(int *A[], int n)
{
  for (int i = parent(n - 1); i >= 0; --i)
    heapify(A, n, i);
}

int main()
{
  int n;
  scanf("%d", &n);
  int N = n;

  int *t = malloc(n * (n + 1) * sizeof(*t));
  int **rows = malloc(n * sizeof(*rows));

  for (int y = 0; y < n; ++y)
  {
    for (int x = 0; x < n; ++x)
      scanf("%d", t + y * (n + 1) + x);
    rows[y] = t + y * (n + 1);
  }

  build_heap(rows, n);

  int *last_print = 0;

  while (n > 0)
  {
    if (last_print == 0 || *rows[0] != *last_print)
      printf("%d ", *rows[0]);
    last_print = rows[0];

    rows[0] += 1;

    if ((rows[0] - t) % (N + 1) == N)
    {
      n -= 1;
      rows[0] = rows[n];
    }

    heapify(rows, n, 0);
  }

  printf("\n");

  free(t);
  free(rows);

  return 0;
}

