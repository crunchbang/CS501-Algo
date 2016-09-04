#include <stdio.h>
#include <stdlib.h>

// sell after l days

void stock_min(int arr[], int n, int l);

int main()
{
        int l;
        scanf("%d", &l);
        int n;
        scanf("%d", &n);
        int arr[n];
        for (int i = 0; i < n; ++i)
                scanf("%d", &arr[i]);
        stock_min(arr, n, l);

        return 0;
}

void stock_min(int arr[], int n, int l)
{
        int max = arr[n-1] - arr[0];
        int i = 0;
        for (int j = l+1; j < n; ++j) 
        {
                if (arr[j] - arr[i] > max)
                        max = arr[j] - arr[i];
                printf("Day %d: Buy @ %d & Sell @ %d\n", j, arr[i], max);
                if (arr[j] < arr[i])
                        i = j;
        }
}
