#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int main(int argc, char *argv[])
{
        long n = atoi(argv[1]);
        FILE *fp = fopen(argv[2], "w");
        long i;
        long limit = pow(10, n);
        srand(time(NULL));
        for (i = 0; i < limit; ++i) {
                int r = rand() % 2;
                fprintf(fp, "%d", r);
        }


}
