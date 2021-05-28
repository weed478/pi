#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

typedef int_fast32_t num_t;

int main()
{
    int n;
    num_t m;
    scanf("%d %" SCNdFAST32, &n, &m);

    int count = 0;

    for (num_t x = 1; x < 1 << n; ++x)
    {
        if (x % m == 0)
            continue;

        num_t mask = 1;
        for (int bit = 0; bit < n; ++bit, mask <<= 1)
        {
            num_t y = x ^ mask;
            if (y != 0 && y % m == 0)
            {
                count++;
                break;
            }
        }
    }

    printf("%d\n", count);

    return 0;
}
