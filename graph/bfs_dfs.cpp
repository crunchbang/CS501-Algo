#include <iostream>
#include <queue>
#include <vector>
#include <utility>

#define INF 1000000
#define VISITED 1

#define WHITE 1
#define GREY 2
#define BLACK 3



using namespace std;

vector< vector<int> > adj_mx;
vector<int> state;
int e, v;

void dfs(int s)
{
    state[s] = GREY;
    cout << s << " ";
    for (int i = 0; i < e; ++i) {
        if (adj_mx[s][i] && state[i] == WHITE) {
            dfs(i);
        }
    }
    state[s] = BLACK;
}

void bfs(int s)
{
    queue<int> q;
    q.push(s);
    state[s] = GREY;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        cout << v << " ";
        for (int i = 0; i < e; ++i)
            if (adj_mx[v][i] && state[i] == WHITE) {
                state[i] = GREY;
                q.push(i);
            }
        state[v] = BLACK;
    }
}


int main()
{
    cin >> v >> e;

    adj_mx.assign(v, vector<int>(v, 0));
    state.assign(v, 0);
    for (int i = 0; i < e; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        //adj_list[u].push_back(make_pair(w, v));
        adj_mx[u][v] = w;
        adj_mx[v][u] = w;
    }

    int start_node = 0;
    fill(state.begin(), state.end(), WHITE);
    cout << "DFS:\n";
    dfs(start_node);

    cout << endl;

    fill(state.begin(), state.end(), WHITE);
    cout << "BFS:\n";
    bfs(start_node);

    return 0;
}
