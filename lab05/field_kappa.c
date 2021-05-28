// by kappa

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n; //size
    if (!scanf("%d", &n)) return -1;

    // create matrix
    int **tab = malloc((unsigned) n * sizeof(*tab));
    for (int i = 0; i < n; i++)
    {
        tab[i] = malloc((unsigned) n * sizeof(tab));
    }

    // fill matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!scanf("%d", &tab[i][j]))return -1;
        }
    }

    /*
     * Solution is to check for every point how far can we go right and down from it's origin
     * and expand area.
     *
     * First we expand area to right (column by column) and remember the limit that we can go to right. Limit is
     * necessary to calculate area. If we encounter '1' in array or we are out of range, the limit is set to it point.
     * At the end of moving right we calculate area and check, if it is greater than maximum.
     * Then we move down (to next row) repeat same process of moving right. Now the difference is that our range is
     * equal to previous limit so we can calculate maximum area from origin.
     */
    int max_area = 0;
    for (int b = 0; b < n; b++)
    {
        for (int a = 0; a < n; a++)
        { //for every point in matrix

            int x = a;
            int y = b;
            int max_x = n;

            // check area for origin point (a,b)
            while (y < n && tab[y][x] == 0)
            {
                while (x < max_x && tab[y][x] == 0)
                {
                    x++;
                }

                // calculate area
                int area = (x - a) * (y - b + 1);
                if (area > max_area)
                {
                    max_area = area;
                }

                max_x = x; // set new right limit

                y++; // move to next row
                x = a; // reset x pointer to row of origin
            }
        }
    }

    printf("%d\n", max_area);

    // free matrix
    for (int i = 0; i < n; i++)
    {
        free(tab[i]);
    }
    free(tab);

    return 0;
}
