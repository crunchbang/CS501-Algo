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
    vector<int> taken(V, 0);

    int min_u, min_v, min_w = INF;
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj_list[u].push_back(make_pair(w, v));
        adj_list[v].push_back(make_pair(w, u));
        if (w < min_w) {
            min_u = u;
            min_v = v;
            min_w = w;
        }
    }

    priority_queue< pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, greater< pair<int, pair<int, int> > > > pq;
    pq.push(make_pair(min_w, make_pair(min_u, min_v)));
    int mst_weight = 0;
    while (!pq.empty()) {
        pair<int, pair<int, int> > item = pq.top();
        pq.pop();
        if (taken[item.second.first] == 1 && taken[item.second.second] == 1)
            continue;
        taken[item.second.first] = taken[item.second.second] = 1;
        mst_weight += item.first;
        cout << "#" << ('a' + item.second.first) << "-" << ('a' + item.second.second) << endl;

        for (int i = 0; i < adj_list[item.second.first].size(); ++i) {
            pair<int, int> x = adj_list[item.second.first][i];
            if (!taken[x.second]) {
                pq.push(make_pair(x.first, make_pair(item.second.first, x.second)));
            }
        }

        for (int i = 0; i < adj_list[item.second.second].size(); ++i) {
            pair<int, int> x = adj_list[item.second.second][i];
            if (!taken[x.second]) {
                pq.push(make_pair(x.first, make_pair(item.second.second, x.second)));
            }
        }
    }
    cout << "weight" << mst_weight;








    return 0;
}
