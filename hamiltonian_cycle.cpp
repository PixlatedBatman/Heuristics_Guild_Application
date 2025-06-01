#include <bits/stdc++.h>
using namespace std;

bool node_available(vector<vector<int>> &roads, vector<int> &path, int pos, int next, int n)
{
    if (!roads[path[pos - 1]][next])
        return false;

    for (int i = 0; i < pos; i++)
    {
        if (path[i] == next)
        {
            return false;
        }
    }

    return true;
}

bool check_cycle(vector<vector<int>> &roads, vector<int> &path, int pos, int n)
{
    if (pos == n)
    {
        return roads[path[n - 1]][0];
    }

    for (int i = 1; i < n; i++)
    {
        if (node_available(roads, path, pos, i, n))
        {
            path[pos] = i;

            if (check_cycle(roads, path, pos + 1, n))
            {
                return true;
            }

            path[pos] = -1;
        }
    }
    return false;
}

vector<int> cycle(vector<vector<int>> &roads, int n)
{
    vector<int> path(n, -1);

    path[0] = 0;

    if (check_cycle(roads, path, 1, n))
    {
        return path;
    }

    return vector<int>(n, -1);
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> roads(n, vector<int>(n, 0));

    int u, v;
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v;

        roads[u][v] = 1;
        roads[v][u] = 1;
    }

    vector<int> path(n, -1);

    path = cycle(roads, n);

    if (path[0] == -1)
    {
        cout << -1 << endl;
        return 0;
    }

    cout << 1 << endl;
    for (auto i : path)
    {
        cout << i << ' ';
    }
    cout << 0 << endl;

    return 0;
}