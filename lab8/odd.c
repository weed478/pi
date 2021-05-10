#include <stdio.h>

typedef long long num_t;

num_t f(num_t x)
{
    while (x % 2 == 0)
        x /= 2;
    return x;
}

num_t naive(num_t N)
{
    num_t res = 0;
    for (num_t i = 1; i <= N; i++)
    {
        res += f(i);
    }

    return res;
}

int div_count(num_t N, num_t a0)
{
    // to samo co floor(log2(2N/a0))
    num_t an = a0;
    int n = 0;
    while (an <= N)
    {
        an *= 2;
        n++;
    }
    return n;
}

num_t big_brain(num_t N)
{
    num_t res = 0;

    for (num_t i = 1; i <= N; i += 2)
    {
        res += div_count(N / 2, i) * i;
        res += i;
    }

    // moment realizacji ze to wlasciwie robi dokladnie to samo

    return res;
}

num_t bigger_brain(num_t N)
{
    num_t res = 0;
    int count = 0;
    num_t count_break = N / 2;

    for (num_t i = N; i >= 1; --i)
    {
        if (i <= count_break)
        {
            count++;
            count_break /= 2;
        }

        if (i % 2 == 0)
            continue;

        res += count * i + i;
    }

    return res;
}

int main()
{
    num_t N;
    scanf("%lld", &N);
    printf("%lld\n", bigger_brain(N));
    return 0;
}
