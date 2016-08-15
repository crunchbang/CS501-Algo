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

int matrix_pow(int N[]);
void matrix_multiply(int dest[][2], int source[][2]);
void divide_by_2(int *n);
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
        /*
        printf("Limit:%ld\n", limit);
        for (int i = msb_index; i <= lsb_index; ++i) 
                printf("%d", N[i]);
        printf("\n");
        */

        printf("f(N): %d\n", matrix_pow(N));
}


int matrix_pow(int N[])
{
        while (is_non_zero(N)) {
                if (N[lsb_index] % 2 != 0) {
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
        int carry = 0;
        int d = 0;
        //printf("\nLimit:%d msb:%d %d lsb:%d %d\n", limit, msb_index, n[msb_index], lsb_index, n[lsb_index]);
        for (int i = msb_index; i <= lsb_index; ++i) {
                d = carry * 10 + n[i];
                carry = d % 2;
                n[i] = d / 2;
        } 
        while (msb_index <= lsb_index && (n[msb_index] == 0)) {
                if (msb_index == lsb_index && n[lsb_index] == 0)
                        return;
                if (n[msb_index] == 0) 
                        msb_index++;
        }
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
        for (int i = lsb_index; i >= msb_index; --i) 
                printf("%d", N[i]);
        printf("\n");
        */
        return N[msb_index] != 0 ? 1 : 0;
}
