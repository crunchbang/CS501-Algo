#include <cstdio>
#include <deque>

using namespace std;
// sell within l days


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
        int max, sell_i, buy_i;
        max = arr[1] - arr[0];
        sell_i = 1;
        buy_i = 0;
        int i;
        deque<int> Q;
        for (i = 0; i < l; ++i) {
                while((!Q.empty()) && (arr[Q.back()] > arr[i])) {
                                Q.pop_back();
                }
                Q.push_back(i);
        }
        for (i = l; i < n; ++i) {
                while(!(Q.empty()) && arr[Q.back()] > arr[i-1])
                        Q.pop_back();
                Q.push_back(i-1);
                while(!(Q.empty()) && Q.front() < (i - l))
                        Q.pop_front();
                int profit = arr[i] - arr[Q.front()];
                if (profit > max) {
                        max = profit;
                        buy_i = Q.front();
                        sell_i = i;
                }
        }
        printf("Buy @ %d - Sell @ %d - Profit %d\n", arr[buy_i], arr[sell_i], max);
}
