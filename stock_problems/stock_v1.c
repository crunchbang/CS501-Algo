#include <stdio.h>
#include <stdlib.h>

/*
 * Stock problem; buy at i sell at j such at a[j] - a[i] is max
 */

void stock_min(int arr[], int n);

int main()
{
        int n;
        scanf("%d", &n);
        int arr[n];
        for (int i = 0; i < n; ++i)
                scanf("%d", &arr[i]);
        stock_min(arr, n);

        return 0;
}

void stock_min(int arr[], int n)
{
        int max = arr[1] - arr[0];
        int i = 0;
        for (int j = 1; j < n; ++j) 
        {
                if (arr[j] - arr[i] > max)
                        max = arr[j] - arr[i];
                printf("Day %d: Buy @ %d & Sell @ %d\n", j, arr[i], max);
                if (arr[j] < arr[i])
                        i = j;
        }
}
