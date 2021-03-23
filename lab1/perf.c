#include <stdio.h>

int is_dosk(int x)
{
  int sum = 1;

  int f = 2;
  for (; f*f < x; f++)
  {
    if (x % f == 0)
    {
      sum += x / f + f;
    }
  }

  if (f*f == x)
  {
    sum += f;
  }

  return sum == x;
}

void find(int min, int max, int count)
{
  int x = max;
  while (x >= min)
  {
    if (is_dosk(x))
    {
      find(min, x - 2, count + 1);
      printf("%d ", x);
      return;
    }
    x -= 2;
  }
  printf("%d\n", count);
}

int main()
{
  int from, to;
  scanf("%d %d", &from, &to);
  
  to = to - to % 2;

  find(from, to, 0);
  printf("\n");

  return 0;
}
