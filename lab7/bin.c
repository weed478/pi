#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool check_num(uint64_t n)
{
    uint8_t last_bit = n & 1;
    n >>= 1;

    while (n > 0)
    {
        uint8_t bit = n & 1;
        if (bit && last_bit)
            return false;

        last_bit = bit;

        n >>= 1;
    }

    return true;
}

void print_bin(uint64_t n, int len)
{
    uint64_t mask = 1 << (len - 1);
    for (int i = 0; i < len; ++i, mask >>= 1)
    {
        printf("%d", (n & mask) > 0);
    }
    printf("\n");
}

int main()
{
    int n;
    int k;
    scanf("%d %d", &n, &k);

    uint64_t i = 0;
    for (; i < 1ull << n; ++i)
    {
        if (check_num(i))
        {
            k--;
            if (k == 0)
                break;
        }
    }

    if (k == 0)
        print_bin(i, n);
    else
        printf("-1\n");

    return 0;
}
