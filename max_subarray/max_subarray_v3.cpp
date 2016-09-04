#include <cstdio>
#include <algorithm>

using namespace std;
// length atleast l


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
        int max_sum, minimum;
        int P[n+1];
        P[0] = 0;
        int i, j, sum = 0;
        for (i = 1; i <= n; ++i) {
                sum += arr[i-1];
                P[i] = sum;
        }
        max_sum = sum = P[l] - P[0];
        minimum = P[0];
        for (i = l+1, j = 1; i <= n; ++i, ++j) {
                minimum = min(minimum, P[j]);
                sum = P[i] - minimum;
                max_sum = max(max_sum, sum);
        }
        printf("Sum of subarray of length atleast %d: %d\n", l, max_sum);
}
