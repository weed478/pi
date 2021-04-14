#include <stdio.h>
#include <stdlib.h>

enum dir_t
{
    RIGHT,
    DOWN,
    LEFT,
    UP,
};

int main()
{
    int n;
    scanf("%d", &n);
    n += 2;

    int *const t = calloc(n * n, sizeof(*t));

    for (int i = 0; i < n; ++i)
    {
        t[i] = 1;
        t[(n - 1) * n + i] = 1;
        t[i * n] = 1;
        t[i * n + n - 1] = 1;
    }

    enum dir_t dir = RIGHT;
    int x = 1;
    int y = 1;

    for (int i = 1; i < (n - 2) * (n - 2); ++i)
    {
        t[y * n + x] = i;

        switch (dir)
        {
            case RIGHT:
                x++;
                break;

            case DOWN:
                y++;
                break;

            case LEFT:
                x--;
                break;

            case UP:
                y--;
                break;
        }

        if (t[y * n + x])
        {
            switch (dir)
            {
                case RIGHT:
                    x--;
                    break;

                case DOWN:
                    y--;
                    break;

                case LEFT:
                    x++;
                    break;

                case UP:
                    y++;
                    break;
            }
            dir = (dir + 1) % 4;
            i--;
        }
    }

    t[y * n + x] = (n - 2) * (n - 2);

    for (y = 1; y < n - 1; ++y)
    {
        for (x = 1; x < n - 1; ++x)
        {
            printf("%d ", t[y * n + x]);
        }
        printf("\n");
    }

    free(t);

    return 0;
}