#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

void quicksort(int arr[], int start, int end);
int partition(int arr[], int start, int end);

int main(int argc, char *argv[])
{
        FILE *fp = fopen(argv[1], "r");
        int n = atoi(argv[2]);

        int arr[n];
        for (int i = 0; i < n; ++i)
                fscanf(fp, "%d", &arr[i]);

        quicksort(arr, 0, n-1);

        printf("Sorted array:\n");
        for (int i = 0; i < n; ++i)
                printf("%d ", arr[i]);

        return 0;
}

void quicksort(int arr[], int start, int end)
{
        if (start <= end) 
        {
                int pivot = partition(arr, start, end);
                quicksort(arr, start, pivot-1);
                quicksort(arr, pivot+1, end);
        }
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

