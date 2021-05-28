#include <stdio.h>

int main()
{
  int x;
  scanf("%d", &x);

  int a = 1;
  int b = 1;

  while (a * b < x)
  {
    int next = a + b;
    a = b;
    b = next;
  }

  if (a * b == x)
    printf("YES\n");
  else
    printf("NO\n");

  return 0;
}

