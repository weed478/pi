#include <stdio.h>

int is_prime(int n)
{
  if (n == 2)
    return 1;
  else if (n % 2 == 0 || n < 2)
    return 0;

  for (int f = 3; f*f <= n; f += 2)
  {
    if (n % f == 0)
      return 0;
  }

  return 1;
}

int max_digit(int n)
{
  int max = 0;
  while (n > 0)
  {
    int d = n % 10;
    if (d > max)
      max = d;
    n /= 10;
  }
  return max;
}

/* 1234565234 -> 1234566666 */
int trim_digits(int x)
{
  int md = max_digit(x);

  int selector = 1;
  while (selector <= x)
  {
    int d = (x / selector) % 10;

    if (d == md)
      break;

    else if (d < md)
      x += selector * (md - d);

    selector *= 10;
  }

  return x;
}

int increment(int x)
{
  if (x % 10 < 9)
    return x + 1;
  else
  {
    x = x + 1;
    x = trim_digits(x);
    return x;
  }
}

int main()
{
  int n;
  scanf("%d", &n);

  for (int i = 2; i < n; i = increment(i))
  {
    if (is_prime(i))
      printf("%d\n", i);
  }

  return 0;
}
