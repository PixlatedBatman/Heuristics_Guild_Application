#include <bits/stdc++.h>
using namespace std;

bool check_cycle(int n, vector<vector<pair<int, int>>> &graph)
{
    vector<int> in_degree(n);

    for (int i = 0; i < n; i++)
    {
        for (auto j : graph[i])
        {
            in_degree[j.first]++;
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
            in_degree[i.first]--;
            if (!in_degree[i.first])
                q.push(i.first);
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