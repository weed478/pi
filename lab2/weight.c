#include <stdio.h>

#define MAX_WEIGHTS (100)
#define abs(x) (x < 0 ? -x : x)

int weight(int w, int tab[], int n, int total)
{
  if (w > total || -w > total)
    return 0;

  else if (n > 0)
    return weight(w + tab[0], tab + 1, n - 1, total - abs(tab[0])) ||
           weight(w         , tab + 1, n - 1, total - abs(tab[0])) ||
           weight(w - tab[0], tab + 1, n - 1, total - abs(tab[0]));

  else
    return w == 0;
}

int main()
{
  int tab[MAX_WEIGHTS];

  int n;
  int w;
  scanf("%d %d", &n, &w);

  int total = 0;

  for (int i = 0; i < n; i++)
  {
    scanf("%d", tab + i);
    total += abs(tab[i]);
  }

  if (weight(w, tab, n, total))
    printf("YES\n");
  else
    printf("NO\n");

  return 0;
}

