#include <stdio.h>
#include <string.h>

#define MAX_ROM_LEN (4 * 4)

static const int lens[] = {
        0,
        1,
        2,
        3,
        2,
        1,
        2,
        3,
        4,
        2,
};

static const char *const units[] = {
        "",       // 0
        "I",      // 1
        "II",     // 2
        "III",    // 3
        "IV",     // 4
        "V",      // 5
        "VI",     // 6
        "VII",    // 7
        "VIII",   // 8
        "IX",     // 9
};

static const char *const tens[] = {
        "",     // 0
        "X",    // 10
        "XX",   // 20
        "XXX",  // 30
        "XL",   // 40
        "L",    // 50
        "LX",   // 60
        "LXX",  // 70
        "LXXX", // 80
        "XC",   // 90
};

static const char *const hundreds[] = {
        "",     // 0
        "C",    // 100
        "CC",   // 200
        "CCC",  // 300
        "CD",   // 400
        "D",    // 500
        "DC",   // 600
        "DCC",  // 700
        "DCCC", // 800
        "CM",   // 900
};

static const char *const thousands[] = {
        "",     // 0
        "M",    // 1000
        "MM",   // 2000
        "MMM",  // 3000
};

enum digit_place_t
{
    UNITS,
    TENS,
    HUNDREDS,
    THOUSANDS,
};

static void printrom_r(int x, enum digit_place_t place)
{
    if (x / 10 > 0)
        printrom_r(x / 10, place + 1);

    switch (place)
    {
        case UNITS:
            printf("%s", units[x % 10]);
            break;

        case TENS:
            printf("%s", tens[x % 10]);
            break;


        case HUNDREDS:
            printf("%s", hundreds[x % 10]);
            break;

        case THOUSANDS:
            printf("%s", thousands[x % 10]);
            break;

        default:
            printf("-"); // error
            break;
    }
}

static inline void printrom(int x)
{
    printrom_r(x, UNITS);
}

enum match_kind_t
{
    MATCH_NONE = -1,
    MATCH_MANY = -2,
};

static int match_rom(const char *s, int n)
{
    int match = MATCH_NONE;
    for (int i = 1; i < 10; ++i)
    {
        if (n == lens[i])
        {
            if (memcmp(s, units[i], n) == 0)
            {
                if (match < 0)
                    match = i;
                else
                    match = MATCH_MANY;
            }

            if (memcmp(s, tens[i], n) == 0)
            {
                if (match < 0)
                    match = i * 10;
                else
                    match = MATCH_MANY;
            }

            if (memcmp(s, hundreds[i], n) == 0)
            {
                if (match < 0)
                    match = i * 100;
                else
                    match = MATCH_MANY;
            }

            if (i <= 3 && memcmp(s, thousands[i], n) == 0)
            {
                if (match < 0)
                    match = i * 1000;
                else
                    match = MATCH_MANY;
            }
        }
    }

    return match;
}

static int rom2int(const char *s)
{
    int x = 0;

    int start = 0;
    int n = 1;

    int last_match = MATCH_NONE;

    while (s[start + n - 1] != 0)
    {
        int new_match = match_rom(s + start, n);

        if (new_match == MATCH_NONE)
        {
            x += last_match;
            start = start + n - 1;
            n = 0;
        }

        last_match = new_match;
        n += 1;
    }

    if (last_match > 0)
        x += last_match;

    return x;
}

int main()
{
    char s1[MAX_ROM_LEN] = {0};
    char s2[MAX_ROM_LEN] = {0};

    scanf("%s %s", s1, s2);

    int a = rom2int(s1);
    int b = rom2int(s2);

    int c = a + b;

    printrom(c);
    printf("\n");

    return 0;
}
