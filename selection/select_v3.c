#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MAX_LEN_NUM 1000000
#define MAX_LEN_RANGE 100

/*
 * Randomized select; uses hoare partition algorithm
 * Usage:
 * <exec> A.txt B.txt
 * Output will be in out.txt
 */

int select(int arr[], int start, int end, int rank);
int partition(int arr[], int start, int end);
void swap(int arr[], int p1, int p2);
int pivot(int arr[], int start, int end);
int cmpfunc (const void * a, const void * b);

int main(int argc, char *argv[])
{
        FILE *fp_num = fopen(argv[1], "r");
        FILE *fp_rank = fopen(argv[2], "r");
        FILE *fp_out = fopen("out.txt", "w");

        int arr[MAX_LEN_NUM];
        int rank[MAX_LEN_RANGE];
        int i;

        srand(time(NULL));

        for (i = 0; i < MAX_LEN_NUM; ++i)
                fscanf(fp_num, "%d", &arr[i]);
        for (i = 0; i < MAX_LEN_RANGE; ++i)
                fscanf(fp_rank, "%d", &rank[i]);
        fclose(fp_num);
        fclose(fp_rank);

        //sort B
        qsort(rank, MAX_LEN_RANGE, sizeof(int), cmpfunc);
        //find index of n/2 element
        int mid_range_i = select(arr, 0, MAX_LEN_NUM-1, rank[MAX_LEN_RANGE / 2]);
        int prev_index = 0;
        int lower, upper;
        int rank_diff;
        for (i = 0; i < MAX_LEN_RANGE; ++i) 
        {
                if (i < MAX_LEN_RANGE/2) {
                        lower = mid_range_i;
                        upper = prev_index-1;
                        rank_diff = rank[i] - rank[i-1];
                        if (upper < lower)
                                printf("%d %d ", lower, upper);
                        if (i == 0) {
                                prev_index = MAX_LEN_NUM-1;
                                rank_diff = rank[i];
                        }
                }
                else {
                        lower = 0;
                        upper = prev_index-1;
                        rank_diff = rank[i] - rank[i-1];
                        if (i == MAX_LEN_RANGE/2) {
                                prev_index = mid_range_i;
                                continue;
                        }
                }
                int ele;
                if (upper < lower)
                        ;
                else 
                        ele = select(arr, lower, upper, rank_diff);
                prev_index = ele;
                fprintf(fp_out, "%d\n", arr[ele]);
        }

        return 0;
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
        if (start == end)
                return start;

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

int cmpfunc (const void * a, const void * b)
{
           return ( *(int*)a - *(int*)b );
}
