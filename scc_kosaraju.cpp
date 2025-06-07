#include <bits/stdc++.h>
using namespace std;

// DFS to find the finishing time of the nodes
void dfs_ft(int node, vector<vector<pair<int, int>>> &graph, stack<int> &finishing_time, vector<int> &visited)
{
    visited[node] = 1;

    for (auto j : graph[node])
    {
        if (!visited[j.first])
            dfs_ft(j.first, graph, finishing_time, visited);
    }

    finishing_time.push(node);
}

// DFS on the reversed edges graph
void dfs_scc(int node, vector<vector<pair<int, int>>> &graph, vector<int> &visited, vector<int> &single_scc)
{
    visited[node] = 1;

    for (auto j : graph[node])
    {
        if (!visited[j.first])
            dfs_scc(j.first, graph, visited, single_scc);
    }

    single_scc.push_back(node);
}

// Function to Find the SCCs of the graph
vector<vector<int>> scc(int n, vector<vector<pair<int, int>>> &graph)
{
    vector<int> visited(n);
    stack<int> finishing_time;

    for (int i = 0; i < n; i++) // DFS to find the finishing time of the nodes
    {
        if (!visited[i])
            dfs_ft(i, graph, finishing_time, visited);
    }

    vector<vector<pair<int, int>>> reversed_graph(n);
    for (int i = 0; i < n; i++) // Reversing the edges of the graph
    {
        for (auto j : graph[i])
        {
            reversed_graph[j.first].push_back(make_pair(i, j.second));
        }
    }

    visited = vector<int>(n, 0);
    vector<vector<int>> vect_scc;
    // Finding the SCCs with DFS on the reversed edge graph
    while (!finishing_time.empty())
    {
        int node = finishing_time.top();
        finishing_time.pop();

        if (!visited[node])
        {
            vector<int> single_scc;
            dfs_scc(node, reversed_graph, visited, single_scc);
            vect_scc.push_back(single_scc);
        }
    }

    return vect_scc;
}

// Raw Topological sorting function
vector<int> topo_sort(int n, vector<vector<int>> &graph)
{
    vector<int> in_degree(n);

    for (int i = 0; i < n; i++)
    {
        for (auto j : graph[i])
            in_degree[j]++;
    }

    queue<int> q;
    for (int i = 0; i < n; i++)
    {
        if (!in_degree[i])
            q.push(i);
    }

    vector<int> topo;
    int node;
    while (!q.empty())
    {
        node = q.front();
        q.pop();
        topo.push_back(node);

        for (auto i : graph[node])
        {
            in_degree[i]--;
            if (!in_degree[i])
                q.push(i);
        }
    }

    return topo;
}

// Function to convert graph into SCCs for topo sorting
vector<int> topo_scc(int n, vector<vector<pair<int, int>>> &graph, vector<vector<int>> &vector_scc)
{
    int n_scc = vector_scc.size();

    vector<int> node_scc(n); // Keys for the SCCs
    for (int i = 0; i < n_scc; i++)
    {
        for (auto j : vector_scc[i])
        {
            node_scc[j] = i;
        }
    }

    vector<unordered_set<int>> adj_scc_set(n_scc); // Set to hold edges between SCCs
    for (int i = 0; i < n; i++)
    {
        for (auto j : graph[i])
        {
            if (node_scc[j.first] != node_scc[i])
                adj_scc_set[node_scc[i]].insert(node_scc[j.first]);
        }
    }

    vector<vector<int>> adj_scc(n_scc);
    for (int i = 0; i < n_scc; i++)
    {
        for (auto j : adj_scc_set[i])
            adj_scc[i].push_back(j);
    }

    return topo_sort(n_scc, adj_scc);
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

    vector<vector<int>> vector_scc = scc(n, graph);               // SCC array
    vector<int> vector_topo_scc = topo_scc(n, graph, vector_scc); // Topo sorted SCCs

    // Printing SCCs
    for (int i = 0; i < vector_scc.size(); i++)
    {
        cout << "SCC" << i << ": ";
        for (auto j : vector_scc[i])
            cout << j << ' ';
        cout << endl;
    }

    // Printing the Topo Sort of the SCCs
    cout << endl
         << "Topograpical sort of SCCs: ";
    for (auto i : vector_topo_scc)
        cout << i << ' ';
    cout << endl;
}