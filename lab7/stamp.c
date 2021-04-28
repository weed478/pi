#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int get_sum(int x0, int y0, const int T[], int n, const int P[], int k, int l)
{
    int sum = 0;
    for (int x = MAX(0, x0); x < MIN(n - 1, x0 + l); ++x)
    {
        for (int y = MAX(0, y0); y < MIN(n - 1, y0 + k); ++y)
        {
            int px = x - x0;
            int py = y - y0;

            if (P[py * l + px])
                sum += T[y * n + x];
        }
    }

    return sum;
}

int main()
{
    int n, k, l;
    scanf("%d %d %d", &n, &k, &l);

    int *const T = malloc(n * n * sizeof *T);
    int *const P = malloc(k * l * sizeof *P);

    for (int i = 0; i < n * n; ++i)
        scanf("%d", &T[i]);

    for(int i = 0; i < k * l; ++i)
        scanf("%d", &P[i]);

    int best_sum = get_sum(-l + 1, -k + 1, T, n, P, k, l);

    for (int x0 = -l + 2; x0 < n; ++x0)
    {
        for (int y0 = -k + 2; y0 < n; ++y0)
        {
            int s = get_sum(x0, y0, T, n, P, k, l);
            if (s > best_sum)
                best_sum = s;
        }
    }

    printf("%d\n", best_sum);

    free(T);
    free(P);
    return 0;
}
