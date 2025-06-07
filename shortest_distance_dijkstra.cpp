#include <bits/stdc++.h>
using namespace std;

// Function to implement Dijkstra's algorithm
vector<int> dijkstra(int n, vector<vector<pair<int, int>>> &graph, int node1)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> distance(n, INT32_MAX);

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
            }
        }
    }
    return distance;
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

    vector<int> distance = dijkstra(n, graph, node1);
    if (distance[node2] != INT32_MAX)
        cout << distance[node2] << endl;
    else
        cout << "There is no valid path from " << node1 << " to " << node2 << endl;
}