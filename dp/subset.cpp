#include <iostream>
#include <vector>

using namespace std;

int N;
vector<int> s;
vector<int> table;

int find_sol(int i) {
    if (i < 0)
        return 0;
    if (table[i] != -1 )
        return table[i];
    int x = find_sol(i-1);
    int y = s[i] + find_sol(i-1);
    table[i] = max(x, y);
    return table[i];
}

int main()
{
    cin >> N;
    table.resize(N+1, -1);
    s.resize(N+1);
    table[0] = 0;
    for (int i = 1; i <= N; ++i)
        cin >> s[i];

    cout << "Max subset sum is " << find_sol(N);

    return 0;
}
