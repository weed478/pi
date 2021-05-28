#include <stdio.h>

int is_prime(int n)
{
  if (n < 2 || n % 2 == 0)
    return 0;

  if (n == 2)
    return 1;

  for (int f = 3; f * f <= n; f += 2)
  {
    if (n % f == 0)
      return 0;
  }

  return 1;
}

int sum_square(int n)
{
  int x = 0;
  while (n > 0)
  {
    int d = n % 10;
    n /= 10;
    x += d * d;
  }
  return x;
}

int process(int n)
{
  while (n != 1 && n != 4)
    n = sum_square(n);
  return n;
}

int main()
{
  int L;
  int U;
  int K;
  scanf("%d %d %d", &L, &U, &K);

  int k = 0;
  for (int i = L; i <= U; ++i)
  {
    if (!is_prime(i))
      continue;

    int res = process(i);
    if (res == 1)
    {
      k += 1;
      if (k == K)
      {
        printf("%d\n", i);
        return 0;
      }
    }
  }

  printf("-1\n");

  return 0;
}

