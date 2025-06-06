#include <bits/stdc++.h>
using namespace std;

bool dfs(int i, vector<vector<pair<int, int>>> &graph, vector<int> &visited, vector<int> &path_visited)
{
    visited[i] = 1;
    path_visited[i] = 1;

    for (auto j : graph[i])
    {
        if (!visited[j.first])
        {
            if (dfs(j.first, graph, visited, path_visited))
                return true;
        }
        else if (path_visited[j.first])
            return true;
    }

    path_visited[i] = 0;
    return false;
}

bool check_cycle(int n, vector<vector<pair<int, int>>> &graph)
{
    vector<int> visited(n), path_visited(n);

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            if (dfs(i, graph, visited, path_visited))
                return true;
        }
    }

    return false;
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

    if (check_cycle(n, graph))
        cout << "Cycle Exists" << endl;
    else
        cout << "Cycle does not exist" << endl;
}