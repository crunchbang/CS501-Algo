#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LEN_NUM 1000000
#define MAX_LEN_RANGE 100

int select(int arr[], int start, int end, int rank);
int partition(int arr[], int start, int end);
int pivot(int arr[], int start, int end);
int median5(int arr[], int start, int end);
void swap(int arr[], int pos1, int pos2);

int main(int argc, char *argv[])
{
        FILE *fp_num = fopen(argv[1], "r");
        FILE *fp_rank = fopen(argv[2], "r");
        FILE *fp_out = fopen("out.txt", "w");

        int arr[MAX_LEN_NUM];
        int rank[MAX_LEN_RANGE];
        int i;

        for (i = 0; i < MAX_LEN_NUM; ++i)
                fscanf(fp_num, "%d", &arr[i]);
        for (i = 0; i < MAX_LEN_RANGE; ++i)
                fscanf(fp_rank, "%d", &rank[i]);

        fclose(fp_num);
        fclose(fp_rank);

        for (i = 0; i < MAX_LEN_RANGE; ++i) 
        {
                /*
                //make copy each time
                int tmp[MAX_LEN_NUM];
                memcpy(tmp, arr, sizeof(arr));
                */
                int ele = select(arr, 0, MAX_LEN_NUM-1, rank[i]);
//                printf("%d\n", arr[ele]);
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

        int i, j, pos;
        i = start - 1;
        j = start;
        pos = pivot(arr, start, end); 
//        pos = end;
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
