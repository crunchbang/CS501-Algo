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

int matrix_pow(int N[]);
void matrix_multiply(int dest[][2], int source[][2]);
void divide_by_2(int *n);
int is_non_zero(int N[]);
void to_binary(int dest[], int source[], int source_lim);


int main(int argc, char *argv[]) 
{
        long size = pow(10, atoi(argv[1]));
        long long max = 4 * size;
        FILE *fp = fopen(argv[2], "r");
        m = atoi(argv[3]);
        int N[max];
        int inp[size];
        char c;
        long k = 0;
        for (long j = 0; j < size; ++j) {
                if ((c = fgetc(fp)) != EOF && isdigit(c)) {
                        inp[k++] = c - '0';
                }
                else 
                        break;
        }
        fclose(fp);
        to_binary(N, inp, k);

        /*
        printf("Binary N:\n");
        for (long j = limit; j >= 0; --j)
                printf("%d", N[j]);
        printf("\n");
        */


        lsb_index = 0;
        msb_index = limit - 1;
        while (N[msb_index] == 0)
                msb_index--;

        printf("f(N): %d\n", matrix_pow(N));
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





int matrix_pow(int N[])
{
        while (is_non_zero(N)) {
        //printf("Limit:%ld msb:%ld %d lsb:%ld %d\n", limit, msb_index, N[msb_index], lsb_index, N[lsb_index]);
                if (N[lsb_index] != 0) {
                        matrix_multiply(Y, A); 
                }
                matrix_multiply(A, A);
                divide_by_2(N);
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

        /*
        for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j)
                        printf("%d ", dest[i][j]);
                printf("\n");
        }
        getchar();
        */
}

void divide_by_2(int n[]) 
{
        //getchar();
        while (msb_index >= lsb_index && (n[msb_index] == 0)) {
                if (msb_index == lsb_index && n[lsb_index] == 0)
                        return;
                if (n[msb_index] == 0) 
                        msb_index--;
                //getchar();
        }
        lsb_index++;
        /*
        printf("\nN:\n");
        for (int i = msb_index; i <= lsb_index; ++i) 
                printf("%d", n[i]);
        printf("\n");
        */

}

int is_non_zero(int N[])
{
        /*
        printf("\nN:\n");
        for (int i = msb_index; i <= lsb_index; ++i) 
                printf("%d", N[i]);
        printf("\n");
        */
        if (msb_index < lsb_index || N[msb_index] == 0)
                return 0;
        else
                return 1;
}
