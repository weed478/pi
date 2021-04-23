#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int newton(int n, int k)
{
    int x = 1;
    for (int i = n; i > n - k; --i)
        x *= i;

    for (int i = 2; i <= k; ++i)
        x /= i;

    return x;
}

typedef struct
{
    int p;
    int q;
} line_t;

static int lines_connected(const line_t *l1, const line_t *l2)
{
    if (l1->p == l2->p ||
        l1->p == l2->q)
        return l1->p;

    if (l1->q == l2->p ||
        l1->q == l2->q)
        return l1->q;

    return 0;
}

static bool create_triangle(const line_t *l1, const line_t *l2, const line_t *l3)
{
    int p1 = lines_connected(l1, l2);
    int p2 = lines_connected(l2, l3);
    int p3 = lines_connected(l3, l1);

    if (p1 == 0 || p2 == 0 || p3 == 0)
        return false;

    if (p1 == p2 || p1 == p3 || p2 == p3)
        return false;

    return true;
}

static int update_triangles(const line_t *l1, const line_t lines[], int n, int points)
{
    int found = 0;
    int lonely = 0;

    for (int i2 = 0; i2 < n; ++i2)
    {
        const line_t *l2 = &lines[i2];

        if (lines_connected(l2, l1))
            lonely++;

        for (int i3 = i2 + 1; i3 < n; ++i3)
        {
            const line_t *l3 = &lines[i3];

            if (create_triangle(l1, l2, l3))
                found++;
        }
    }

    lonely -= found * 2;

    return found - (points - 2 - lonely - found);
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    int n_tri = newton(n, 3);

    line_t *const lines = malloc(m * sizeof lines[0]);

    for (int i = 0; i < m; ++i)
    {
        line_t *l = &lines[i];
        scanf("%d %d", &l->p, &l->q);

        n_tri += update_triangles(l, lines, i, n);
    }

    printf("%d\n", n_tri);

    free(lines);

    return 0;
}
