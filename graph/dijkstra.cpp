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
    priority_queue< pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    vector<int> distance(V, INF);
    //assuming start node to be 0
    int start_node = 0;
    pq.push(make_pair(0, start_node));
    distance[start_node] = 0;
    while (!pq.empty()) {
        pair<int, int> p = pq.top();
        pq.pop();
        int d = p.first;
        int u = p.second;
        if (d > distance[u])
            continue;
        for (int i = 0; i < adj_list[u].size(); ++i) {
            int w = adj_list[u][i].first;
            int v = adj_list[u][i].second;
            if (distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
                pq.push(make_pair(distance[v], v));
            }
        }
    }

    cout << "Distances\n";
    for (int i = 0; i < V; ++i) {
        cout << start_node << "->" << i << " " << distance[i] << endl;
    }

    return 0;
}
