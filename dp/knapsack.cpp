#include <iostream>
#include <vector>

using namespace std;

int N, W;
vector<int> w, p;
vector< vector<int> > table;
//int table[1000][1000] = {{-1}};

int find_sol(int i, int j) {
    if (i < 0 || j < 0)
        return 0;
    if (table[i][j] != -1 ) {
        return table[i][j];
    }
    int x = find_sol(i-1, j);
    int y = j >= w[i] ? (p[i] + find_sol(i-1, j-w[i])) : 0;
    table[i][j] = max(x, y);
    return table[i][j];
}

int main()
{

    cin >> N;
    cin >> W;
    w.resize(N+1, 0);
    p.resize(N+1, 0);
    table.reserve(N+1);
    for (int i = 0; i <= N; ++i) {
        table[i].resize(W+1, -1);
        table[i][0] = 0;
    }
    fill(table[0].begin(), table[0].end(), 0);

    for (int i = 1; i <= N; ++i) {
        cin >> w[i] >> p[i];
    }

    cout << "Max profit with weight constraint " << W << "kg:";
    cout << find_sol(N, W);

    return 0;
}
