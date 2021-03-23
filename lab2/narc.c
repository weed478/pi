#include <stdio.h>
#include <stdint.h>

typedef uint64_t num_t;

const char HEX_DIGITS[] = "0123456789ABCDEF";

void print_base(num_t n, int b)
{
    if (n / b)
        print_base(n / b, b);
    printf("%c", HEX_DIGITS[n % b]);
}

num_t pow_int(int a, int b){
    num_t x = 1;
    for (int i = 0; i < b; ++i)
    {
        x *= a;
    }
    return x;
}

num_t get_digit_map(num_t n, int n_digits, int base)
{
    num_t digit_map = 0;
    while (n > 0)
    {
        num_t d = n % base;
        n /= base;
        digit_map += pow_int(n_digits + 1, d);
    }
    return digit_map;
}

num_t get_sump(num_t digit_map, int n_digits, int len, int base)
{
    digit_map /= n_digits + 1;
    num_t sum = 0;
    for (int d = 1; d < base; ++d)
    {
        num_t d_count = digit_map % (n_digits + 1);
        digit_map /= n_digits + 1;
        sum += d_count * pow_int(d, len);
    }
    return sum;
}

num_t test_sump(num_t digit_map, int n_digits, int len, int base)
{
    num_t sump = get_sump(digit_map, n_digits, len, base);
    if (get_digit_map(sump, n_digits, base) == digit_map)
        return sump;
    else
        return 0;
}

int for_all_combos(int n_digits, int depth, num_t digit_map, int c_len, int base)
{
    int found = 0;
    if (depth == 0)
    {
        if (c_len == n_digits)
        {
            num_t num = test_sump(digit_map, n_digits, c_len, base);
            if (num)
            {
                print_base(num, base);
                printf(" ");
                found = 1;
            }
        }
    }
    else
    {
        for (int i = 0; i <= n_digits - c_len; ++i)
        {
            found |= for_all_combos(n_digits, depth - 1, digit_map * (n_digits + 1) + i, c_len + i, base);
        }
    }
    return found;
}

void armstrong(int n_digits, int base)
{
    if (!for_all_combos(n_digits, base, 0, 0, base))
        printf("NO");
    printf("\n");
}

int main()
{
    int m;
    int b;
    scanf("%d %d", &m, &b);

    armstrong(m, b);

    return 0;
}

