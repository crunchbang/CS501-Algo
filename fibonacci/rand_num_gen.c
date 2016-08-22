#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

/*
 * Usage
 * executable <n> <file_name> <base>
 * 10 ^ n digit number will be generated and stored in <file_name>
 */

int main(int argc, char *argv[])
{
        long n = atoi(argv[1]);
        FILE *fp = fopen(argv[2], "w");
        int base = atoi(argv[3]);
        long i;
        long limit = pow(10, n);
        srand(time(NULL));
        for (i = 0; i < limit; ++i) {
                int r = rand() % base;
                fprintf(fp, "%d", r);
        }


}
