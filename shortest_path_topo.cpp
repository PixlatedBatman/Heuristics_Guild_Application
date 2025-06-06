#include <bits/stdc++.h>
using namespace std;

void dfs(int node, vector<vector<pair<int, int>>> &graph, stack<int> &topo, vector<int> &visited)
{
    visited[node] = 1;

    for (auto j : graph[node])
    {
        if (!visited[j.first])
            dfs(j.first, graph, topo, visited);
    }

    topo.push(node);
}

int shortest_path(int n, vector<vector<pair<int, int>>> &graph, int node1, int node2)
{
    stack<int> topo;
    vector<int> visited(n);
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
            dfs(i, graph, topo, visited);
    }

    vector<int> distance(n, INT32_MAX);
    distance[node1] = 0;
    while (!topo.empty())
    {
        int node = topo.top();
        topo.pop();

        for (auto i : graph[node])
        {
            distance[i.first] = min(distance[i.first], distance[node] + i.second);
        }
    }

    return distance[node2];
}

int main()
{
    // Assumption for input: n vertices and m edges in the directed graph
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> graph(n, vector<pair<int, int>>(0));

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

    int path_length = shortest_path(n, graph, node1, node2);

    if (path_length != INT32_MAX)
        cout << path_length << endl;
    else
        cout << "There is no valid path from " << node1 << " to " << node2 << endl;
}