#include <iostream>
#include <vector>

using namespace std;

#define INF 1000003

#define COST_R 2
#define COST_D 1
#define COST_A 3

int N;
string s1, s2;
vector<vector<int> > table;

int find_sol(int i, int j) {
    if (i == 0)
        return j * COST_D;
    if (j == 0)
        return j * COST_D;
    if (table[i][j] != INF) {
        return table[i][j];
    }
    if (s1[i] == s2[j]) {
        table[i][j] = find_sol(i-1, j-1);
    }
    else {
        int c;
        c = find_sol(i-1, j-1) + COST_R;
        c = min(c, find_sol(i, j-1) + COST_A);
        c = min(c, find_sol(i-1, j) + COST_D);
        table[i][j] = c;
    }
    return table[i][j];
}

int main()
{

    cin >> s1 >> s2;
    int n1 = s1.size(), n2 = s2.size();
    int N = max(n1, n2);
    table.resize(N+1, vector<int>(N+1, INF));
    table[0][0] = 0;

    cout << "Min edit distance:" << find_sol(n1, n2);

    return 0;
}
