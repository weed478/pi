#include <stdio.h>

#define MAX_N (1000)

int main()
{
  int tab[MAX_N];

  int n;
  scanf("%d", &n);

  int sum = 0;

  for (int i = 0; i < n; i++)
  {
    scanf("%d", tab + i);
    sum += tab[i];
  }

  int half = 0;
  for (int i = 0; i < n; i++)
  {
    sum -= tab[i];
    if (half == sum)
    {
      printf("%d\n", i);
      break;
    }
    half += tab[i];
  }

  return 0;
}

