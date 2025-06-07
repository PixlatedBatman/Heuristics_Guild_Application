#include <bits/stdc++.h>
using namespace std;

// Function to implement Dijkstra's algorithm to find path
vector<int> dijkstra(int n, vector<vector<pair<int, int>>> &graph, int node1, int node2)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> distance(n, INT32_MAX);
    vector<int> parent(n);
    for (int i = 0; i < n; i++)
        parent[i] = i;

    distance[node1] = 0;
    pq.push(make_pair(0, node1));

    while (!pq.empty())
    {
        int dist = pq.top().first; // Choosing minimum distance pair
        int node = pq.top().second;
        pq.pop();

        for (auto i : graph[node])
        {
            if (dist + i.second < distance[i.first])
            {
                distance[i.first] = dist + i.second;
                pq.push(make_pair(distance[i.first], i.first));
                parent[i.first] = node;
            }
        }
    }

    if (distance[node2] == INT32_MAX)
        return {-1};

    vector<int> path;
    int node = node2;
    while (parent[node] != node)
    {
        path.push_back(node);
        node = parent[node];
    }
    path.push_back(node1);
    reverse(path.begin(), path.end());
    return path;
}

int main()
{
    // Assumption for input: n vertices and m edges in the directed graph
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> graph(n);

    int u, v, w;
    for (int i = 0; i < m; i++)
    {
        // Assumption for input: edge is directed from u to v with weight w; 0 indexed
        cin >> u >> v >> w;
        graph[u].push_back(make_pair(v, w));
    }

    // Assumption for input: Required distance is from node1 to node2
    int node1, node2;
    cin >> node1 >> node2;

    vector<int> path = dijkstra(n, graph, node1, node2);
    if (path[0] == -1)
    {
        cout << "There is no valid path from " << node1 << " to " << node2 << endl;
        return 0;
    }

    for (auto i : path)
        cout << i << ' ';
    cout << endl;
}