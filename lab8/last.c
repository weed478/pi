#include <stdio.h>

typedef long long num_t;

int main()
{
    num_t n;
    scanf("%lld", &n);

    num_t base = 1;
    while (n / base != 0)
        base = base * 10 + 1;
    base /= 10;

    num_t X = 0;
    while (base > 0)
    {
        X *= 10;

        if (n / base > 9)
        {
            X = -1;
            break;
        }

        X += n / base;
        n = n % base;
        base /= 10;
    }

    printf("%lld\n", X);

    return 0;
}
