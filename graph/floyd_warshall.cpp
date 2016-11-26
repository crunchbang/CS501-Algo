#include <iostream>
#include <queue>
#include <vector>
#include <utility>

#define INF 1000000

using namespace std;


int main()
{
    int E, V;
    cin >> V >> E;
    //vector< vector< pair<int, int> > >adj_list(V);
    vector< vector<int> > adj_mx(V, vector<int>(V, INF));
    vector< vector<int> > distances(V, vector<int>(V, INF));

    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        //adj_list[u].push_back(make_pair(w, v));
        adj_mx[u][v] = w;
        distances[u][v] = w;
    }

    for (int i = 0; i < V; ++i)
        distances[i][i] = 0;

    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j)
                distances[i][j] = min(distances[i][k] + distances[k][j], distances[i][j]);
        }
    }




    cout << "Distances\n";
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            cout << i << "->" << j << " " << distances[i][j] << endl;
        }
    }

    return 0;
}
