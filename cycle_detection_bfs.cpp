#include <bits/stdc++.h>
using namespace std;

bool check_cycle(int n, vector<vector<int>> &graph)
{
    vector<int> in_degree(n);

    for (int i = 0; i < n; i++)
    {
        for (auto j : graph[i])
        {
            in_degree[j]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < n; i++)
    {
        if (!in_degree[i])
            q.push(i);
    }

    int topo_sort_count = 0, node;
    while (!q.empty())
    {
        node = q.front();
        q.pop();
        topo_sort_count++;

        for (auto i : graph[node])
        {
            in_degree[i]--;
            if (!in_degree[i])
                q.push(i);
        }
    }

    if (topo_sort_count < n)
        return true;
    else
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