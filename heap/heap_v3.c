#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>

/*
 *  N : 10^6
 *  k : 10^4
 *  Same as v2 but using random pivot
 */

#define N 1000000
#define K 10000

int select(int arr[], int start, int end, int rank);
int partition(int arr[], int start, int end);
int pivot(int arr[], int start, int end);
void swap(int arr[], int pos1, int pos2);
void find_min_k(char *input, char *output);

int main(int argc, char *argv[])
{
        char *input = argv[1];
        char *output = "output_v3.txt";
        srand(time(NULL));
        find_min_k(input, output);

        return 0;
}

void find_min_k(char *input, char *output)
{
        FILE *ifp = fopen(input, "r");
        FILE *ofp = fopen(output, "w");
        int arr[2*K];
        int n = 0;
        for (int i = 0; i < 2*K; ++i)
                fscanf(ifp, "%d", &arr[i]);
        n += 2*K;
        while (n < N) {
                int p = 0;
                while (p < K) {
                        p = partition(arr, 0, 2 * K - 1);
                }
                for (int i = p; i < 2*K && n < N; ++i, ++n)
                        fscanf(ifp, "%d", &arr[i]);
        }
        select(arr, 0, 2 * K - 1, K);
        for (int i = 0; i < K; ++i)
                fprintf(ofp, "%d\n", arr[i]);
}

int select(int arr[], int start, int end, int rank)
{
        if (start == end)
                return start;
        int pos = partition(arr, start, end);
        int r = end - pos + 1;
        if (r == rank) 
                return pos;
        if (rank > r)
                return select(arr, start, pos-1, rank-r);
        else
                return select(arr, pos+1, end, rank);

}

int partition(int arr[], int start, int end)
{

        int i, j, pos;
        i = start - 1;
        j = start;
        pos = pivot(arr, start, end); 
        swap(arr, pos, end);
        while (j < end) 
        {
                if (arr[j] <= arr[end]) 
                {
                        i = i + 1;
                        swap(arr, i, j);
                }
                j++;
        }
        i = i + 1;
        swap(arr, i, end);
        return i;
}

int pivot(int arr[], int start, int end)
{
        int p = start + rand() % (end - start + 1);
        return p;
}

void swap(int arr[], int p1, int p2) 
{
        int t = arr[p1];
        arr[p1] = arr[p2];
        arr[p2] = t;
}
