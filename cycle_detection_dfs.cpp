#include <bits/stdc++.h>
using namespace std;

bool dfs(int i, vector<vector<int>> &graph, vector<int> &visited, vector<int> &path_visited)
{
    visited[i] = 1;
    path_visited[i] = 1;

    for (auto j : graph[i])
    {
        if (!visited[j])
        {
            if (dfs(j, graph, visited, path_visited))
                return true;
        }
        else if (path_visited[j])
            return true;
    }

    path_visited[i] = 0;
    return false;
}

bool check_cycle(int n, vector<vector<int>> &graph)
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
    vector<vector<int>> graph(n, vector<int>(0));

    int u, v;
    for (int i = 0; i < m; i++)
    {
        // Assumption for input: edge is directed from u to v; both 0 indexed
        cin >> u >> v;
        graph[u].push_back(v);
    }

    if (check_cycle(n, graph))
        cout << "Cycle Exists" << endl;
    else
        cout << "Cycle does not exist" << endl;
}