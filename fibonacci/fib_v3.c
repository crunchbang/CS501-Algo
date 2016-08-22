/*
 * V3
 * Input as decimal
 * Convert into binary
 * O((lg n) ^ 2) complexity
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

int matrix_pow(int num[]);
void matrix_multiply(int dest[][2], int source[][2]);
void divide_by_2(int num[]);
int is_non_zero(int num[]);
void to_binary(int dest[], int source[], int source_lim);


int main(int argc, char *argv[]) 
{
        long size = pow(10, atoi(argv[1]));
        long long max = 4 * size;
        FILE *fp = fopen(argv[2], "r");
        m = atoi(argv[3]);
        int bin_inp[max];
        int dec_inp[size];
        char c;
        long k = 0;
        for (long j = 0; j < size; ++j) {
                if ((c = fgetc(fp)) != EOF && isdigit(c)) {
                        dec_inp[k++] = c - '0';
                }
                else 
                        break;
        }
        fclose(fp);

        to_binary(bin_inp, dec_inp, k);
        lsb_index = 0;
        msb_index = limit - 1;
        while (bin_inp[msb_index] == 0)
                msb_index--;

        printf("f(inp): %d\n", matrix_pow(bin_inp));
}

void to_binary(int dest[], int source[], int source_lim)
{

        int carry, d;
        long long msb = 0;
        long long lsb = source_lim - 1;
        int flag = 1;
        int j = 0;
        while (flag) {
                carry = d = 0;
                for (int i = msb; i <= lsb; ++i) {
                        d = carry * 10 + source[i];
                        carry = d % 2;
                        source[i] = d / 2;
                } 
                dest[j++] = carry;
                while (msb <= lsb && (source[msb] == 0)) {
                        if (msb == lsb) {
                                flag = 0;
                                break;
                        }
                        else
                                msb++;
                }
        }
        limit = j;
}

int matrix_pow(int num[])
{
        while (is_non_zero(num)) {
                if (num[lsb_index] != 0) {
                        matrix_multiply(Y, A); 
                }
                matrix_multiply(A, A);
                divide_by_2(num);
        }
        return Y[0][1];
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

void divide_by_2(int num[]) 
{
        while (msb_index >= lsb_index && (num[msb_index] == 0)) {
                if (msb_index == lsb_index && num[lsb_index] == 0)
                        return;
                if (num[msb_index] == 0) 
                        msb_index--;
        }
        lsb_index++;

}

int is_non_zero(int num[])
{
        if (msb_index < lsb_index || num[msb_index] == 0)
                return 0;
        else
                return 1;
}

