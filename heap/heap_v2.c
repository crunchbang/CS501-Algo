#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/*
 *  N : 10^6
 *  k : 10^4
 *  Create an array of 2k elements
 *  Find element with rank k
 *  Replace last k elements with new elements
 *  Repeat until entire file is read
 *
 *  Usage:
 *  <exec> <input_file>
 *  Output: 
 *  output_v1.txt
 */

#define N 1000000
#define K 10000


int select(int arr[], int start, int end, int rank);
int partition(int arr[], int start, int end);
int pivot(int arr[], int start, int end);
int median5(int arr[], int start, int end);
void swap(int arr[], int pos1, int pos2);
void find_min_k(char *input, char *output);

int main(int argc, char *argv[])
{
        char *input = argv[1];
        char *output = "output_v2.txt";
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
                int p = select(arr, 0, 2 * K - 1, K);
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
        if (end - start <= 5)
                return median5(arr, start, end);
        for (int i = start; i <= end; i = i + 5) 
        {
                int sub_end = i + 4;
                if (sub_end > end)
                        sub_end = end;
                int med_pos = median5(arr, i, sub_end);
                //swap to the beginning of the list
                int loc = start + ((i - start)/5);
                swap(arr, loc, med_pos);
        }
        return pivot(arr, start, start + ceil((end - start)/5) - 1); 
}

int median5(int arr[], int start, int end)
{
        int p = (end - start)/2;
        for (int i = start; i <= end; ++i) 
        {
                int max = i;
                for (int j = i + 1; j < end; ++j)
                        if (arr[j] > arr[max])
                                max = j;
                swap(arr, i, max);
        }
        return start+p;
}

void swap(int arr[], int p1, int p2) 
{
        int t = arr[p1];
        arr[p1] = arr[p2];
        arr[p2] = t;
}
