#include <iostream>
#include <vector>

#define INF 1000003

using namespace std;

int N;
vector<int> m;
vector<vector<int> > table;

int find_sol(int i, int j) {
    if (i > j) {
        return 0;
    }
    if (table[i][j] != INF) {
        return table[i][j];
    }
    for (int k = i; k < j; ++k)
        table[i][j] = min(table[i][j], find_sol(i,k) + find_sol(k+1, j) + m[i-1] * m[k] * m[j]);

    return table[i][j];
}

int main()
{
    cin >> N;
    m.resize(N+1, -1);
    for (int i = 0; i < N; ++i)
        cin >> m[i];
    table.resize(N+1, vector<int>(N+1, INF));
    for (int i = 0; i <= N; ++i)
        table[i][i] = 0;

    cout << "Min no of mult:" << find_sol(1, N-1);

    return 0;
}
