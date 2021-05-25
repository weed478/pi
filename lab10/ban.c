#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

#define N_ATM (100)

void solve(uint64_t x, bool flip_control)
{
    bool borrow[N_ATM + 1];
    borrow[N_ATM] = false;
    bool A[N_ATM];
    bool B[N_ATM];
    bool C[N_ATM];

    for (int i = 0; i < N_ATM; ++i)
    {
        borrow[i] = false;
        A[i] = 0;
        B[i] = 0;
        C[i] = x & 1;
        x >>= 1;
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

void solve_withdrawal(uint64_t x)
{
    solve(x, false);
}

void solve_deposit(uint64_t x)
{
    solve(x, true);
}

int main()
{
    uint64_t x;
    scanf("%" SCNu64, &x);
    solve_withdrawal(x);
    solve_deposit(x);

    return 0;
}
