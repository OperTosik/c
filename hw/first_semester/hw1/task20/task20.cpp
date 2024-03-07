#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int f20(FILE *f);

int main(void) {
    FILE *f = fopen("input.txt", "rt");
    if (f == NULL) {
        perror("Couldn't open an input file");
        return -1;
    }

    FILE *g = fopen("output.txt", "wt");
    if (g == NULL) {
        perror("Couldn't open an output file");
        return -1;
    }

    fprintf(g, "%d\n", f20(f));
    fclose(f);
    fclose(g);
    return 0;
}

int f20(FILE *f) {
    int prevnum = 0, currnum = 0;
    int currlen = 1, longestlen = 1;
    if(fscanf(f, "%d\n", &prevnum) != 1)
    {
        fclose(f);
        return 1;
    }

    while (fscanf(f, "%d\n", &currnum) == 1)
    {
        if (currnum == prevnum)
        {
            currlen ++;
        }
        else
        {
            if(currlen > longestlen)
            {
                longestlen = currlen;
            }
        currlen = 1;
        }
        prevnum = currnum;
    }
    if (currlen > longestlen)
    {
        longestlen = currlen;
    }
    return longestlen;
}
