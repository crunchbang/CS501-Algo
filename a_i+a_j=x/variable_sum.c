#include <stdio.h>
#include <stdlib.h>

/*
 * Find i, j, k such that a[i] + a[j] = a[k]
 */

int find_indices(int arr[], int n, int sum);
int find_indices_wrapper(int arr[], int n);
int cmp_fn(const void *a,const void *b);

int main()
{
        int n;
        scanf("%d", &n);
        int arr[n];
        for (int i = 0; i < n; ++i)
                scanf("%d", &arr[i]);
        if (find_indices_wrapper(arr, n) == -1)
                printf("None\n");


        return 0;
}

int cmp_fn(const void *a,const void *b)
{
        return (*(int *)a - *(int *)b);
}

int find_indices_wrapper(int arr[], int n) 
{
        qsort(arr, n, sizeof(int), cmp_fn);
        int status = -1;
        for (int i = 0; i < n; ++i)
                if(find_indices(arr, n, arr[i]) == 1) {
                        status = 1;
                        break;
                }
        return status;
}

int find_indices(int arr[], int n, int sum)
{
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
                return -1;
        else
                printf("%d + %d = %d\n", arr[left], arr[right], sum);
        return 1;
}
