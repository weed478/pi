#include <stdio.h>
#include <string.h>

#define COUNT_OF(t) (sizeof t / sizeof *t)

#define MAX_LEN (64)

static int PRIMES[MAX_LEN];

static void sieve(int t[], int n)
{
    t[0] = 0;

    for (int i = 2; i <= n; ++i)
        t[i - 1] = i;

    for (int p = 2; p <= n; ++p)
    {
        if (t[p - 1] == 0)
            continue;

        for (int k = p * 2; k <= n; k += p)
            t[k - 1] = 0;
    }
}

void compress_primes(int t[], int n)
{
    for (int i = 1; i < n; ++i)
    {
        for (int j = i; j - 1 >= 0 && t[j - 1] == 0; --j)
        {
            t[j - 1] = t[j];
            t[j] = 0;
        }
    }
}

void make_string(const char s[], int o, int p, int n, char output[])
{
    for (int i = 0; i < n; ++i)
    {
        output[i] = s[(o + p * i) % n];
    }
    output[n] = 0;
}

void make_best_string(const char input[], char output[], int n)
{
    char buf[MAX_LEN + 1];
    output[0] = 0;

    for (int o = 0; o < n; ++o)
    {
        for (int p_i = 0; PRIMES[p_i] && PRIMES[p_i] < n; ++p_i)
        {
            int p = PRIMES[p_i];

            make_string(input, o, p, n, buf);

            if (output[0] == 0 || strncmp(output, buf, n) > 0)
                strncpy(output, buf, n + 1);
        }
    }
}

int main()
{
    sieve(PRIMES, COUNT_OF(PRIMES));
    compress_primes(PRIMES, COUNT_OF(PRIMES));

    char text[MAX_LEN + 1];
    scanf("%s", text);
    int n = strlen(text);

    char solution[MAX_LEN + 1];
    make_best_string(text, solution, n);

    printf("%s\n", solution);

    return 0;
}
