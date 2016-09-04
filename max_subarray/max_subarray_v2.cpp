#include <cstdio>
#include <algorithm>

using namespace std;
// length l


void max_subarray(int arr[], int n, int l);

int main()
{
        int l;
        scanf("%d", &l);
        int n;
        scanf("%d", &n);
        int arr[n];
        for (int i = 0; i < n; ++i)
                scanf("%d", &arr[i]);
        max_subarray(arr, n, l);

        return 0;
}

void max_subarray(int arr[], int n, int l)
{
        int sum = 0; 
        int max_sum;
        int i;
        for (i = 0; i < l; ++i)
                sum += arr[i];
        max_sum = sum;
        for (int i = l; i < n; ++i) {
                sum = sum + arr[i] - arr[i-l];
                max_sum = max(max_sum, sum);
        }
        printf("Max:%d\n", max_sum);

}
