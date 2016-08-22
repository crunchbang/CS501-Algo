#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LEN_NUM 1000000
#define MAX_LEN_RANGE 100

int select(int arr[], int start, int end, int rank);
int partition(int arr[], int start, int end);

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

//        printf("Size:%ld", sizeof(arr));


        for (i = 0; i < MAX_LEN_RANGE; ++i) 
        {
                //make copy each time
                int tmp[MAX_LEN_NUM];
                memcpy(tmp, arr, sizeof(arr));
                int ele = select(tmp, 0, MAX_LEN_NUM-1, rank[i]);
                printf("%d\n", tmp[ele]);
                fprintf(fp_out, "%d\n", tmp[ele]);
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

        int i, j, r, t;
        i = start - 1;
        j = start;
        r = arr[end];
        while (j < end) 
        {
                if (arr[j] <= r) 
                {
                        i = i + 1;
                        t = arr[i];
                        arr[i] = arr[j];
                        arr[j] = t;
                }
                j++;
        }
        i = i + 1;
        t = arr[i];
        arr[i] = arr[end];
        arr[end] = t;
        return i;
}

