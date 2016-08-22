/*
 * V5
 * Find period of the given sequence
 * Complexity - ??
 * Usage:
 * exec <n> <input_file> <m>
 * Input number can contain max 10 ^ n digits
 * Input file contatins the number
 */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

int precompute(long n, int mem[]);
int big_mod(int num[], int len, int period);

long m;

int main(int argc, char *argv[])
{
        long max = pow(10, atoi(argv[1]));
        FILE *fp = fopen(argv[2], "r");
        m = atol(argv[3]);
        int inp[max];
        int c;
        int len = 0;
        while ((c = fgetc(fp)) != EOF && isdigit(c)) {
                inp[len++] = c - '0';
        }
        fclose(fp);

        int mem[6 * m + 1];

        precompute(6 * m, mem);
        long period = 0;
        for (long i = 2; i <= 6 * m; ++i)
                if (mem[i] == 0 && mem[i+1] == 1) {
                        period = i;
                        break;
                }

        int p = big_mod(inp, len, period);
        printf("f(N): %d", mem[p]);

        return 0;
}

int precompute(long n, int mem[]) 
{
        mem[0] = 0;
        mem[1] = 1;
        for (long i = 2; i <= n; ++i)
                mem[i] = (mem[i-1] + mem[i-2]) % m;
        return mem[n];
}

int big_mod(int num[], int len, int period)
{
        long d = 0;
        long carry = 0;
        for (long i = 0; i < len; ++i) {
                d = carry * 10 + num[i];
                carry = d % period;
        }
        return carry;
}
