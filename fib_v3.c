#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

int A[2][2] = { {1, 1},
                {1, 0} };
int Y[2][2] = { {1, 0},
                {0, 1}};
long limit;
long msb_index;
long lsb_index;
long m;

void matrix_pow(int A[][2], int y);
int f(int N[]);
void matrix_multiply(int dest[][2], int source[][2]);
void divide_by_10(int *n);
int is_non_zero(int N[]);


int main(int argc, char *argv[]) 
{
        long max = pow(10, atoi(argv[1]));
        FILE *fp = fopen(argv[2], "r");
        m = atoi(argv[3]);
        int N[max];
        char c;
        limit = 0;
        for (long j = 0; j < max; ++j) {
                if ((c = fgetc(fp)) != EOF && isdigit(c)) {
                        N[limit++] = c - '0';
                }
                else 
                        break;
        }
        fclose(fp);

        msb_index = 0;
        lsb_index = limit - 1;
        while (N[msb_index] == 0)
                msb_index++;

        printf("f(N): %d\n", f(N));
}


int f(int N[])
{
        while (is_non_zero(N)) {
                int T[2][2];
                for (int i = 0; i < 2; ++i)
                        for (int j = 0; j < 2; ++j)
                                T[i][j] = A[i][j];
                matrix_pow(T, N[lsb_index]);
                matrix_multiply(Y, T); 

                matrix_pow(A, 10);
                divide_by_10(N);
        }
        return Y[0][1];
}

void matrix_pow(int A[][2], int y)
{
        int X[2][2] = { { 1, 0 }, { 0, 1 } };
        while (y != 0) {
                if (y % 2 != 0) {
                        matrix_multiply(X, A); 
                }
                matrix_multiply(A, A);
                y = y / 2;
        }
        for (int i = 0; i < 2; ++i) 
                for (int j = 0; j < 2; ++j) 
                        A[i][j] = X[i][j];
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

void divide_by_10(int n[]) 
{
        lsb_index--;
}

int is_non_zero(int N[])
{
        if (msb_index > lsb_index || N[msb_index] == 0)
                return 0;
        return 1;
}
