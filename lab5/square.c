#include <stdio.h>
#include <stdlib.h>

static inline int in_bounds(int r, int x, int y, int n)
{
    return x + r < n &&
           x - r >= 0 &&
           y + r < n &&
           y - r >= 0;
}

static int sum_border(int r, int x0, int y0, int n, int t[][n])
{
    int sum = 0;

    for (int x = x0 - r; x <= x0 + r; ++x)
    {
        sum += t[y0 - r][x] + t[y0 + r][x];
    }

    for (int y = y0 - r + 1; y <= y0 + r - 1; ++y)
    {
        sum += t[y][x0 - r] + t[y][x0 + r];
    }

    return sum;
}

void find_squares(int k, int n, int t[][n], int count, int x, int y, int r)
{
    for (; y >= 0; --y)
    {
        for (; x >= 0; --x)
        {
            for (; in_bounds(r, x, y, n); ++r)
            {
                int sum = sum_border(r, x, y, n, t);
                if (sum == k)
                {
                    find_squares(k, n, t, count + 1, x, y, r + 1);
                    printf("%d %d\n", y, x);
                    return;
                }
            }
            r = 1;
        }
        x = n - 1;
    }

    printf("%d\n", count);
}

int main()
{
    int n;
    int k;
    scanf("%d %d", &n, &k);

    int (*const t)[n] = malloc(n * n * sizeof(**t));

    for (int i = 0; i < n * n; ++i)
        scanf("%d", &t[i / n][i % n]);

    find_squares(k, n, t, 0, n - 1, n - 1, 1);

    free(t);

    return 0;
}
