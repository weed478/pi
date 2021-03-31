#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct BigInt
{
  uint8_t *digits;
  int len;
  int max_len;
};

void bi_init(struct BigInt *x, int max_digits)
{
  x->digits = malloc(max_digits * sizeof(*x->digits));
  x->digits[0] = 0;
  x->len = 1;
  x->max_len = max_digits;
}

void bi_free(struct BigInt *x)
{
  free(x->digits);
  x->len = 0;
  x->max_len = 0;
}

struct BigInt bi_new(int max_digits)
{
  struct BigInt x;
  bi_init(&x, max_digits);
  return x;
}

void bi_set(struct BigInt *x, int y)
{
  x->len = 0;
 
  do {
    x->digits[x->len] = y % 10;
    x->len += 1;
    y /= 10;
  } while (y > 0);
}

void bi_print(struct BigInt *x)
{
  for (int i = x->len - 1; i >= 0; --i)
  {
    printf("%d", x->digits[i]);
  }
}

void bi_mul(struct BigInt *x, int y)
{
  int carry = 0;

  for (int i = 0; i < x->len; ++i)
  {
    int new_digit = x->digits[i] * y + carry;
    x->digits[i] = new_digit % 10;
    carry = new_digit / 10;
  }

  while (carry > 0)
  {
    x->digits[x->len] = carry % 10;
    x->len += 1;
    carry /= 10;
  }
}

int main()
{
  int n;
  scanf("%d", &n);

  struct BigInt x = bi_new(256);

  bi_set(&x, 1);

  for (int i = 2; i <= n; ++i)
    bi_mul(&x, i);

  bi_print(&x);
  printf("\n");

  bi_free(&x);
  return 0;
}

