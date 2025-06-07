#include <bits/stdc++.h>
using namespace std;

class DisjointSet
{
private:
    vector<int> rank, parent;

public:
    DisjointSet(int n)
    {
        rank.resize(n, 0);
        parent.resize(n);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find_Uparent(int node)
    {
        if (parent[node] == node)
            return node;

        return parent[node] = find_Uparent(parent[node]);
    }

    void union_rank(int u, int v)
    {
        int u_Uparent = find_Uparent(u);
        int v_Uparent = find_Uparent(v);

        if (u_Uparent == v_Uparent)
            return;

        if (rank[u_Uparent] < rank[v_Uparent])
            parent[u_Uparent] = v_Uparent;
        else if (rank[u_Uparent] > rank[v_Uparent])
            parent[v_Uparent] = u_Uparent;
        else
        {
            parent[v_Uparent] = u_Uparent;
            rank[u_Uparent]++;
        }
    }
};

// Function to find the weight of the minimum spanning tree of a graph
int mst_kruskal(int n, vector<vector<pair<int, int>>> &graph)
{
    // Vector to store the edges to sort based on weight
    vector<pair<int, pair<int, int>>> edges; // {weight, {u, v}}
    for (int i = 0; i < n; i++)
    {
        for (auto j : graph[i])
        {
            edges.push_back(make_pair(j.second, make_pair(i, j.first)));
        }
    }
    sort(edges.begin(), edges.end());

    // Defining disjoing set for the nodes.
    int weight_mst = 0;
    DisjointSet ds(n);
    for (auto i : edges)
    {
        int w = i.first, u = i.second.first, v = i.second.second;

        if (ds.find_Uparent(u) != ds.find_Uparent(v)) // If Part of different structure
        {
            ds.union_rank(u, v);
            weight_mst += w;
        }
    }

    return weight_mst;
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

    int mst_weight = mst_kruskal(n, graph);
    cout << "Weight of MST: " << mst_weight << endl;
}