#include <stdio.h>
#include <stdlib.h>

int get_area(int x1, int y1, int x2, int y2)
{
    return (abs(x2 - x1) + 1) * (abs(y2 - y1) + 1);
}

int check_free_row(const int field[], int n, int y, int x1, int x2)
{
    if (x2 < x1)
    {
        int tmp = x2;
        x2 = x1;
        x1 = tmp;
    }

    for (int x = x1; x <= x2; ++x)
    {
        if (field[y * n + x])
            return 0;
    }

    return 1;
}

int main()
{
    int n;
    scanf("%d", &n);

    int *const field = malloc(n * n * sizeof(*field));

    for (int i = 0; i < n * n; ++i)
    {
        scanf("%d", field + i);
    }

    int max_area = 0;

    for (int x1 = 0; x1 < n; ++x1)
    {
        for (int x2 = x1; x2 < n; ++x2)
        {
            for (int y1 = 0; y1 < n; ++y1)
            {
                for (int y2 = y1; y2 < n; ++y2)
                {
                    if (!check_free_row(field, n, y2, x1, x2))
                    {
                        y1 = y2;
                        break;
                    }

                    int area = get_area(x1, y1, x2, y2);
                    if (area > max_area)
                        max_area = area;
                }
            }
        }
    }

    printf("%d\n", max_area);

    free(field);

    return 0;
}
