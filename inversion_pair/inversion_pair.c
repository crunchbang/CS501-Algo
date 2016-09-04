#include <stdio.h>
#include <stdlib.h>

// maximum number of inversion pairs

int inversion_pair(int arr[], int start, int end);
int merge_inversion_pair(int arr[], int start, int mid, int end);

int main()
{
        int n;
        scanf("%d", &n);
        int arr[n];
        for (int i = 0; i < n; ++i)
                scanf("%d", &arr[i]);

        for (int j = 0; j < n; ++j)
                printf("%d ", arr[j]);
        printf("\n");
        printf("Number of inversion pairs: %d\n", inversion_pair(arr, 0, n-1));
        for (int j = 0; j < n; ++j)
                printf("%d ", arr[j]);
        printf("\n");
        return 0;
}

int inversion_pair(int arr[], int start, int end)
{
        if (start == end)
                return 0;
        else 
        {
                int c = 0;
                int mid = (start + end) / 2;
                int c1 = inversion_pair(arr, start, mid);
                int c2 = inversion_pair(arr, mid + 1, end);
                int c3 = merge_inversion_pair(arr, start, mid, end);
                c = c1 + c2 + c3;
                return c;
        }
}

int merge_inversion_pair(int arr[], int start, int mid, int end)
{
        int c = 0;
        int left = start;
        int right = mid + 1;
        int b[end - start + 1];
        int i = 0;
        while (left <= mid && right <= end) {
                if (arr[left] <= arr[right]) {
                        b[i] = arr[left];
                        i++;
                        left++;
                }
                else {
                        c += (mid - left + 1);
                        b[i] = arr[right];
                        i++;
                        right++;
                }
        }
        while (left <= mid) {
                b[i] = arr[left];
                i++;
                left++;
        }
        while (right <= end) {
                b[i] = arr[right];
                i++;
                right++;
        }
        for (int j = start; j <= end ; ++j)
                arr[j] = b[j - start];
        return c;
}
