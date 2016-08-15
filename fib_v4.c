/*
 * V4
 * Input as decimal
 * Exponentation using power of 10 thing
 * O(lg n) complexity
 * Usage:
 * exec <n> <input_file> <m>
 * Input number can contain max 10 ^ n digits
 * Input file contatins the number
 */
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

int A[2][2] = { {1, 1},
                {1, 0} };
int Y[2][2] = { {1, 0},
                {0, 1} };
long limit;
long msb_index;
long lsb_index;
long m;

void matrix_pow(int mx[][2], int x);
int f(int num[]);
void matrix_multiply(int dest[][2], int source[][2]);
void divide_by_10(int num[]);
int is_non_zero(int num[]);


int main(int argc, char *argv[]) 
{
        long max = pow(10, atoi(argv[1]));
        FILE *fp = fopen(argv[2], "r");
        m = atoi(argv[3]);
        int inp[max];
        char c;

        limit = 0;
        for (long j = 0; j < max; ++j) {
                if ((c = fgetc(fp)) != EOF && isdigit(c)) {
                        inp[limit++] = c - '0';
                }
                else 
                        break;
        }
        fclose(fp);

        msb_index = 0;
        lsb_index = limit - 1;
        while (inp[msb_index] == 0)
                msb_index++;
        printf("f(inp): %d\n", f(inp));
}


int f(int num[])
{
        while (is_non_zero(num)) {
                int temp[2][2];
                for (int i = 0; i < 2; ++i)
                        for (int j = 0; j < 2; ++j)
                                temp[i][j] = A[i][j];
                matrix_pow(temp, num[lsb_index]);
                matrix_multiply(Y, temp); 

                matrix_pow(A, 10);
                divide_by_10(num);
        }
        return Y[0][1];
}

void matrix_pow(int mx[][2], int x) // modifies mx to store mx ^ x
{
        int res[2][2] = { { 1, 0 }, { 0, 1 } };
        while (x != 0) {
                if (x % 2 != 0) {
                        matrix_multiply(res, mx); 
                }
                matrix_multiply(mx, mx);
                x = x / 2;
        }
        for (int i = 0; i < 2; ++i) 
                for (int j = 0; j < 2; ++j) 
                        mx[i][j] = res[i][j];
}


void matrix_multiply(int dest[][2], int source[][2])
{
        int temp[2][2];
        temp[0][0] = dest[0][0] * source[0][0] + dest[0][1] * source[1][0];
        temp[0][1] = dest[0][0] * source[0][1] + dest[0][1] * source[1][1];
        temp[1][0] = dest[1][0] * source[0][0] + dest[1][1] * source[1][0];
        temp[1][1] = dest[1][0] * source[0][1] + dest[1][1] * source[1][1];
        for (int i = 0; i < 2; ++i)
                for (int j = 0; j < 2; ++j)
                        dest[i][j] = temp[i][j] % m;
}

void divide_by_10(int num[]) 
{
        lsb_index--;
}

int is_non_zero(int num[])
{
        if (msb_index > lsb_index || num[msb_index] == 0)
                return 0;
        return 1;
}
