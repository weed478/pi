#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define N_INPUTS (128)
#define N_GATES (3100)

enum signal_type_t
{
    SIG_INPUT,
    SIG_XOR,
};

struct xor_t
{
    struct signal_t *in1;
    struct signal_t *in2;
};

struct signal_t
{
    enum signal_type_t type;
    bool cached;
    bool value;
    union
    {
        struct xor_t xor;
    };
};

bool eval(struct signal_t *sig)
{
    if (sig->cached)
        return sig->value;

    switch (sig->type)
    {
        case SIG_INPUT:
            break;

        case SIG_XOR:
            sig->value = eval(sig->xor.in1) != eval(sig->xor.in2);
            break;
    }

    sig->cached = true;
    return sig->value;
}

void init_xor(struct signal_t *gate, struct signal_t *in1, struct signal_t *in2)
{
    gate->type = SIG_XOR;
    gate->cached = false;
    gate->xor.in1 = in1;
    gate->xor.in2 = in2;
}

void reset_xor(struct signal_t *gate)
{
    gate->cached = false;
}

void reset_gates(struct signal_t gates[], int n_gates)
{
    for (int i = 0; i < n_gates; ++i)
        reset_xor(&gates[i]);
}

void init_input(struct signal_t *input, bool value)
{
    input->type = SIG_INPUT;
    input->value = value;
    input->cached = true;
}

int char2int(char c)
{
    return c - '0';
}

char int2char(int i)
{
    return '0' + i;
}

void step_binary(char bin[], int n)
{
    int carry = 1;
    for (int i = n - 1; i >= 0; --i)
    {
        int x = char2int(bin[i]) + carry;
        carry = x / 2;
        bin[i] = int2char(x % 2);
    }
}

void rjustify(char num[], int n)
{
    int offset = n - strnlen(num, n);

    for (int i = n - 1; i >= offset; --i)
        num[i] = num[i - offset];

    for (int i = 0; i < offset; ++i)
        num[i] = '0';
}

void load_inputs(struct signal_t inputs[], int n_inputs, char bin[], int n_chars)
{
    for (int i = 0; i < n_inputs; ++i)
        init_input(&inputs[i], char2int(bin[n_chars - n_inputs + i]));
}

int main()
{
    int n_inputs;
    int n_gates;
    int out_gate;
    scanf("%d %d %d", &n_inputs, &n_gates, &out_gate);
    out_gate--;

    struct signal_t inputs[N_INPUTS];
    struct signal_t gates[N_GATES];

    for (int i = 0; i < n_gates; ++i)
    {
        int in1;
        int in2;
        scanf("%d %d", &in1, &in2);

        init_xor(&gates[i],
                 in1 < 0 ? &inputs[-in1 - 1] : &gates[in1 - 1],
                 in2 < 0 ? &inputs[-in2 - 1] : &gates[in2 - 1]);
    }

    char in_lo[N_INPUTS + 1];
    char in_hi[N_INPUTS + 1];

    in_lo[N_INPUTS] = 0;
    in_hi[N_INPUTS] = 0;

    scanf("%s", in_lo);
    scanf("%s", in_hi);

    rjustify(in_lo, N_INPUTS);
    rjustify(in_hi, N_INPUTS);

    int count = 0;

    for (;;)
    {
        reset_gates(gates, n_gates);
        load_inputs(inputs, n_inputs, in_lo, N_INPUTS);
        bool res = eval(&gates[out_gate]);
        if (res)
            count++;

        if (strncmp(in_lo, in_hi, N_INPUTS) == 0)
            break;

        step_binary(in_lo, N_INPUTS);
    }

    printf("%d\n", count);

    return 0;
}

