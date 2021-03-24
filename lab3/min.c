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

void heapify(int A[], int n, int i)
{
  int m = i;
  do
  {
    i = m;
    int l = left(m);
    int r = right(m);

    if (l < n && A[l] > A[m])
      m = l;

    if (r < n && A[r] > A[m])
      m = r;

    int tmp = A[i];
    A[i] = A[m];
    A[m] = tmp;
  } while (m != i);
}

void build_heap(int A[], int n)
{
  for (int i = parent(n - 1); i >= 0; --i)
    heapify(A, n, i);
}

void minimize(int tab[], int n, int k)
{
  for (int i = 0; i < k; ++i)
  {
    tab[0] /= 2;
    heapify(tab, n, 0);
  }
}

int sum(int tab[], int n)
{
  int s = 0;
  for (int i = 0; i < n; ++i)
    s += tab[i];
  return s;
}

int main()
{
  int n;
  int k;
  scanf("%d %d", &n, &k);

  int *tab = malloc(n * sizeof(*tab));

  for (int i = 0; i < n; ++i)
    scanf("%d", tab + i);

  build_heap(tab, n);
  minimize(tab, n, k);

  int s = sum(tab, n);
  printf("%d\n", s);

  free(tab);
  return 0;
}

