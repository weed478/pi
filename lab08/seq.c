#include <stdio.h>
#include <stdbool.h>

#define MAX_LEN (64)

bool is_alpha(char c)
{
    return c >= 'a' && c <= 'z';
}

int find_first_special(const char text[])
{
    int i;
    for (i = 0; text[i] != 0; ++i)
    {
        if (!is_alpha(text[i]))
            break;
    }
    return i;
}

const char* find_biggest_char(const char text[])
{
    if (*text == 0)
        return text;

    const char *best = text;

    for (const char *c = text + 1; *c != 0; ++c)
    {
        if (*c > *best)
            best = c;
    }

    return best;
}

int main()
{
    char input[MAX_LEN + 1];
    scanf("%s", input);

    // trim \n \r
    input[find_first_special(input)] = 0;

    const char *text = input;
    char output[MAX_LEN + 1];
    int out_len = 0;

    while (*text != 0)
    {
        const char *best = find_biggest_char(text);

        output[out_len] = *best;
        out_len++;

        text = best + 1;
    }

    output[out_len] = 0;

    printf("%s\n", output);

    return 0;
}
