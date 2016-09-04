#include <cstdio>
#include <algorithm>
#include <deque>

using namespace std;
// length atmost l


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
        int P[n+1];
        P[0] = 0;
        int i, sum = 0;
        for (i = 1; i <= n; ++i) {
                sum += arr[i-1];
                P[i] = sum;
        }
        int max, end_i, start_i;
        max = P[1] - P[0];
        end_i = 1;
        start_i = 0;
        deque<int> Q;
        for (i = 0; i < l; ++i) {
                while((!Q.empty()) && (P[Q.back()] > P[i])) {
                                Q.pop_back();
                }
                Q.push_back(i);
        }
        for (i = l+1; i <= n; ++i) {
                while(!(Q.empty()) && P[Q.back()] > P[i-1])
                        Q.pop_back();
                Q.push_back(i-1);
                while(!(Q.empty()) && Q.front() < (i - l))
                        Q.pop_front();
                int sum = P[i] - P[Q.front()];
                if (sum > max) {
                        max = sum;
                        start_i = Q.front();
                        end_i = i;
                }
        }
        printf("Sum of subarray of size utmost %d: %d", l, max);
}
