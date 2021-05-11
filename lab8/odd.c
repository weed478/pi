#include <stdio.h>

typedef long long num_t;

num_t odd_numbers_upto(num_t n)
{
    return ((n + 1) / 2) * ((n + 1) / 2);
}

num_t odd_numbers_between(num_t a, num_t b)
{
    return odd_numbers_upto(b) - odd_numbers_upto(a - 1);
}

num_t biggest_brain(num_t N)
{
    num_t res = odd_numbers_upto(N);

    int count = 1;
    num_t count_break = N / 2;

    while (count_break >= 1)
    {
        res += count * odd_numbers_between(count_break / 2 + 1, count_break);
        count_break /= 2;
        count++;
    }

    return res;
}

int main()
{
    num_t N;
    scanf("%lld", &N);
    printf("%lld\n", biggest_brain(N));
    return 0;
}
