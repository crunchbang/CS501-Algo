#include <cstdio>
#include <algorithm>

using namespace std;
// min length subarry which contains all elements 
// from 1..k
// INCORRECT
// NEEDS REVISION


void max_subarray(int arr[], int n, int k);

int main()
{
        int k;
        scanf("%d", &k);
        int n;
        scanf("%d", &n);
        int arr[n];
        for (int i = 0; i < n; ++i)
                scanf("%d", &arr[i]);
        max_subarray(arr, n, k);

        return 0;
}

void max_subarray(int arr[], int n, int k)
{
        int i;
        int map[k+1];
        for (i = 0; i < k+1; ++i)
                map[i] = 0;
        for (i = 0; i < n; ++i)
                if(arr[i] <= k)
                        map[arr[i]]++;
        int start_i = 0;
        int end_i = n - 1;
        while (1) {
                while(arr[end_i] > k) 
                        end_i--;
                if (map[arr[end_i]] <= 1) 
                        break;
                else {
                        map[arr[end_i]]--;
                        end_i--;
                }
        }
        while (1) {
                while(arr[end_i] > k) 
                        start_i++;
                if (map[arr[start_i]] <= 1) 
                        break;
                else {
                        map[arr[start_i]]--;
                        start_i++;
                }
        }
        printf("Length: %d\n", (end_i - start_i + 1));
        for (i = start_i; i <= end_i; ++i)
                printf("%d ", arr[i]);
        printf("\n");
}
