#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define X_MIN (-100)
#define X_MAX (100)
#define Y_MIN (-100)
#define Y_MAX (100)

#define FIELD_W (X_MAX - X_MIN + 1)
#define FIELD_H (Y_MAX - Y_MIN + 1)

typedef enum
{
    WHITE = 0,
    BLACK,
} color_t;

typedef struct
{
    int x1;
    int y1;

    int x2;
    int y2;

    color_t *squares;
} rect_t;

static inline int r_width(rect_t r)
{
    return abs(r.x1 - r.x2);
}

static inline int r_height(rect_t r)
{
    return abs(r.y1 - r.y2);
}

static inline void sort_coords(int *x1, int *x2)
{
    if (*x2 < *x1)
    {
        int tmp = *x2;
        *x2 = *x1;
        *x1 = tmp;
    }
}

static inline bool r_contains(rect_t r, int x, int y)
{
    return r.x1 <= x && x < r.x2 &&
           r.y1 <= y && y < r.y2;
}

static void color_overlap(rect_t *target, const rect_t *source)
{
    for (int x = 0; x < r_width(*target); ++x)
    {
        for (int y = 0; y < r_height(*target); ++y)
        {
            if (r_contains(*source, target->x1 + x, target->y1 + y))
            {
                if (target->squares[y * r_width(*target) + x] == WHITE)
                    target->squares[y * r_width(*target) + x] = BLACK;
                else
                    target->squares[y * r_width(*target) + x] = WHITE;
            }
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    rect_t field;
    field.x1 = X_MIN;
    field.y1 = Y_MIN;
    field.x2 = X_MAX + 1;
    field.y2 = Y_MAX + 1;

    static color_t field_squares[FIELD_H][FIELD_W] = {0};
    field.squares = (color_t*) field_squares;

    for (int i = 0; i < n; ++i)
    {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

        sort_coords(&x1, &x2);
        sort_coords(&y1, &y2);

        rect_t r;
        r.x1 = x1;
        r.y1 = y1;
        r.x2 = x2;
        r.y2 = y2;

        color_overlap(&field, &r);
    }

    int blacks = 0;
    for (int x = 0; x < FIELD_W; ++x)
        for (int y = 0; y < FIELD_H; ++y)
            if (field.squares[y * FIELD_W + x] == BLACK)
                blacks++;

    printf("%d\n", blacks);

    return 0;
}
