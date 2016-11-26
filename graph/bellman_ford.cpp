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
    vector< vector< pair<int, int> > >adj_list(V);

    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj_list[u].push_back(make_pair(w, v));
    }

    vector<int> distance(V, INF);
    int start_node = 0;
    distance[start_node] = 0;
    for (int k = 0; k < V-1; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < adj_list[i].size(); ++j) {
                pair<int, int> p = adj_list[i][j];
                int w = p.first;
                int v = p.second;
                distance[v] = min(distance[i] + w, distance[v]);

            }
        }
    }


    cout << "Distances\n";
    for (int i = 0; i < V; ++i) {
        cout << start_node << "->" << i << " " << distance[i] << endl;
    }

    return 0;
}
