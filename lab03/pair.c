#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
  return *(int*)a - *(int*)b;
}

void quicksort(int A[], int p, int r)
{
  qsort(A + p, r - p, sizeof(*A), cmp);
}

int count_pairs(int A[], int n, int k)
{
  int pairs = 0;
  for (int i = 1; i < n - 1;)
  {
    int x = A[i];
    int l = A[i - 1];

    int j = i + 1;
    for (; j < n - 1 && A[j] == x; ++j);

    int r = A[j];

    if ((l != x && abs(l - x) <= k) || (r != x && abs(r - x) <= k))
      pairs += j - i;

    i = j;
  }
  return pairs;
}

int main()
{
  int n;
  int k;
  scanf("%d %d", &n, &k);
  n += 2;

  int *tab = malloc(n * sizeof(*tab));

  for (int i = 1; i < n - 1; ++i)
    scanf("%d", tab + i);

  quicksort(tab, 1, n - 1);

  tab[0] = tab[1];
  tab[n - 1] = tab[n - 2];

  int pairs = count_pairs(tab, n, k);
  printf("%d\n", pairs);

  free(tab);
  return 0;
}

