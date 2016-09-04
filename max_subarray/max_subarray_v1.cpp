#include <cstdio>
#include <algorithm>

using namespace std;


void max_subarray(int arr[], int n);

int main()
{
        int n;
        scanf("%d", &n);
        int arr[n];
        for (int i = 0; i < n; ++i)
                scanf("%d", &arr[i]);
        max_subarray(arr, n);

        return 0;
}

void max_subarray(int arr[], int n)
{
        int sum = 0;
        int max_sum = 0;
        for (int i = 0; i < n; ++i) {
                sum = max(sum + arr[i], 0);
                max_sum = max(max_sum, sum);
        }
        printf("Max:%d\n", max_sum);

}
