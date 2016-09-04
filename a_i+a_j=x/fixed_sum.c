#include <stdio.h>
#include <stdlib.h>

/*
 * Given X find i, j such that a[i] + a[j] = X
 */

void find_indices(int arr[], int n, int sum);
int cmp_fn(const void *a,const void *b);

int main()
{
        int sum;
        scanf("%d", &sum);
        int n;
        scanf("%d", &n);
        int arr[n];
        for (int i = 0; i < n; ++i)
                scanf("%d", &arr[i]);
        find_indices(arr, n, sum);

        return 0;
}


int cmp_fn(const void *a,const void *b)
{
        return (*(int *)a - *(int *)b);
}

void find_indices(int arr[], int n, int sum)
{
        qsort(arr, n, sizeof(int), cmp_fn);
        int left = 0;
        int right = n-1;
        while (left < right) 
        {
                int s = arr[left] + arr[right];
                if (s == sum) 
                {
                        break;
                }
                else if (s < sum)
                        left++;
                else 
                        right--;
        }
        if (left >= right)
                printf("None\n");
        else
                printf("%d + %d = %d\n", arr[left], arr[right], sum);
}
