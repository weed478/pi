#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int n;
    int i;
} tl_args_t;

typedef int (*tl_fn_t)(int i, const tl_args_t*);

int wrap_array(int x, int y, int n)
{
    x = (n + (x % n)) % n;
    y = (n + (y % n)) % n;
    return y * n + x;
}

int translate_row(int i, const tl_args_t *args)
{
    return wrap_array(i, args->i, args->n);
}

int translate_col(int i, const tl_args_t *args)
{
    return wrap_array(args->i, i, args->n);
}

int translate_diag_up(int i, const tl_args_t *args)
{
    int x0 = 0;
    int y0 = args->i;

    int x = x0 + i;
    int y = y0 - i;

    return wrap_array(x, y, args->n);
}

int translate_diag_down(int i, const tl_args_t *args)
{
    int x0 = 0;
    int y0 = args->n - 1 - args->i;

    int x = x0 + i;
    int y = y0 + i;

    return wrap_array(x, y, args->n);
}

int find_best_line(int k, int line_len, const int t[], tl_fn_t tl, const tl_args_t *tl_args)
{
    int sum = 0;
    for (int i = 0; i < k; ++i)
        sum += t[tl(i, tl_args)];

    int max_sum = sum;
    int start = 0;

    do
    {
        if (sum > max_sum)
            max_sum = sum;

        sum -= t[tl(start, tl_args)];
        start++;
        sum += t[tl(start + k - 1, tl_args)];
    } while (start % line_len != 0);

    return max_sum;
}

int get_max(int best, int k, int line_len, const int t[], tl_fn_t translator, tl_args_t tl_args, int tl_len)
{
    for (tl_args.i = 0; tl_args.i < tl_len; ++tl_args.i)
    {
        int s = find_best_line(k, line_len, t, translator, &tl_args);
        if (s > best)
            best = s;
    }
    return best;
}

int main()
{
    int n;
    int k;
    scanf("%d %d", &n, &k);

    int *const t = malloc(n * n * sizeof *t);

    for (int i = 0; i < n * n; ++i)
            scanf("%d", &t[i]);

    tl_args_t tl_args;
    tl_args.n = n;

    tl_args.i = 0;
    int best_sum = find_best_line(k, n, t, translate_row, &tl_args);

    best_sum = get_max(best_sum, k, n, t, translate_row, tl_args, n);
    best_sum = get_max(best_sum, k, n, t, translate_col, tl_args, n);
    best_sum = get_max(best_sum, k, n, t, translate_diag_up, tl_args, 2 * n - 1);
    best_sum = get_max(best_sum, k, n, t, translate_diag_down, tl_args, 2 * n - 1);

    printf("%d\n", best_sum);

    free(t);
    return 0;
}
