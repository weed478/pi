#include <stdio.h>

#define MAX_N (64)

typedef long long int num_t;

#define N_BITS (60)

void erase_invalid(num_t t[], const int n, const num_t g)
{
    for (int i = 0; i < n; ++i)
    {
        num_t x = t[i];
        num_t y = g;
        for (int bit = 0; bit < N_BITS; ++bit, x >>= 1, y >>= 1)
        {
            if (x & 1 && !(y & 1))
            {
                t[i] = 0;
                break;
            }
        }
    }
}

int find_solution(const num_t t[], const int n, const num_t g)
{
    int bit_counts[N_BITS] = {0};

    for (int i = 0; i < n; ++i)
    {
        num_t x = t[i];
        for (int bit = 0; bit < N_BITS; ++bit, x >>= 1)
        {
            if (x & 1)
                bit_counts[bit]++;
        }
    }

    int min_count = -1;
    num_t x = g;
    for (int bit = 0; bit < N_BITS; ++bit, x >>= 1)
    {
        if (x & 1 && (min_count < 0 || bit_counts[bit] < min_count))
            min_count = bit_counts[bit];
    }

    return min_count < 0 ? 0 : min_count;
}

int main()
{
    int n;
    num_t g;
    scanf("%d %lld", &n, &g);

    num_t t[MAX_N];

    for (int i = 0; i < n; ++i)
        scanf("%lld", &t[i]);

    erase_invalid(t, n, g);

    int x = find_solution(t, n, g);
    printf("%d\n", x);

    return 0;
}
