#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define N_ATM (100)
#define N_DIGITS (64)

void solve(const bool C[], bool flip_control)
{
    bool borrow[N_ATM + 1];
    borrow[N_ATM] = false;
    bool A[N_ATM];
    bool B[N_ATM];

    for (int i = 0; i < N_ATM; ++i)
    {
        borrow[i] = false;
        A[i] = 0;
        B[i] = 0;
    }

    for (int i = 0; i < N_ATM; ++i)
    {
        bool a;
        bool b;
        bool need_borrow;

        if (i % 2 == flip_control)
        {
            // set A

            if (C[i])
            {
                // need 1

                if (borrow[i])
                {
                    a = 0;
                    need_borrow = true;
                }
                else
                {
                    a = 1;
                    need_borrow = false;
                }
            }
            else
            {
                // need 0

                if (borrow[i])
                {
                    a = 1;
                    need_borrow = false;
                }
                else
                {
                    a = 0;
                    need_borrow = false;
                }
            }

            A[i] = a;
        }
        else
        {
            // set B

            if (C[i])
            {
                // need 1

                if (borrow[i])
                {
                    b = 0;
                    need_borrow = true;
                }
                else
                {
                    b = 1;
                    need_borrow = true;
                }
            }
            else
            {
                // need 0

                if (borrow[i])
                {
                    b = 1;
                    need_borrow = true;
                }
                else
                {
                    b = 0;
                    need_borrow = false;
                }
            }

            B[i] = b;
        }

        borrow[i + 1] = need_borrow;
    }

    if (borrow[N_ATM])
    {
        printf("NO\n");
    }
    else
    {
        for (int i = 0; i < N_ATM; ++i)
        {
            if (A[i] || B[i])
                printf("%d ", i);
        }
        printf("\n");
    }
}

void solve_withdrawal(const bool C[])
{
    solve(C, false);
}

void solve_deposit(const bool C[])
{
    solve(C, true);
}

int char2int(char c)
{
    return c - '0';
}

char int2char(int i)
{
    return '0' + i;
}

int div2(char num[])
{
    int remainder = 0;
    for (int i = 0; i < N_DIGITS; ++i)
    {
        remainder *= 10;
        remainder += char2int(num[i]);
        num[i] = int2char(remainder / 2);
        remainder %= 2;
    }
    return remainder;
}

void char_to_bits(char number[], bool bits[])
{
    for (int i = 0; i < N_ATM; ++i)
    {
        bits[i] = div2(number);
    }
}

void rjustify(char num[])
{
    int offset = N_DIGITS - strnlen(num, N_DIGITS);

    for (int i = N_DIGITS - 1; i >= offset; --i)
        num[i] = num[i - offset];

    for (int i = 0; i < offset; ++i)
        num[i] = '0';
}

int main()
{
    char number[N_DIGITS + 1];
    number[N_DIGITS] = 0;

    scanf("%s", number);
    rjustify(number);

    bool bits[N_ATM];
    char_to_bits(number, bits);

    solve_withdrawal(bits);
    solve_deposit(bits);

    return 0;
}
