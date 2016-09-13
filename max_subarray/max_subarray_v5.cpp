#include <cstdio>
#include <algorithm>

using namespace std;
// min subarray with sum > S
// for arrays containing positive elements
// INCORRECT
// NEEDS REVISION


void max_subarray(int arr[], int n, int s);

int main()
{
        int s;
        scanf("%d", &s);
        int n;
        scanf("%d", &n);
        int arr[n];
        for (int i = 0; i < n; ++i)
                scanf("%d", &arr[i]);
        max_subarray(arr, n, s);

        return 0;
}

void max_subarray(int arr[], int n, int s)
{
        int min_len = n;
        int j = 0;
        int sum = 0;
        for (int i = 0; i < n; ++i) {
                sum += arr[i];
                while (sum > s && j <= i) {
                        min_len = min(min_len, i - j + 1);
                        sum -= arr[j++];
                }
        }
        printf("Length: %d\n", min_len);
}
