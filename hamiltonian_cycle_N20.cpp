#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> check_cycle(int n, vector<vector<int>> &roads)
{

    vector<vector<bool>> dp(n, vector<bool>(1 << n, false));
    vector<vector<int>> parent(n, vector<int>(1 << n, -1));

    for (int i = 0; i < n; i++)
        dp[i][1 << i] = true;

    for (int i = 0; i < (1 << n); i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i & 1 << j)
            {
                for (int k = 0; k < n; k++)
                {
                    if ((i & 1 << k) && roads[k][j] && k != j && dp[k][i ^ (1 << j)])
                    {
                        dp[j][i] = true;
                        parent[j][i] = k;
                    }
                }
            }
        }
    }

    vector<int> path;
    int end_node = -1;

    for (int i = 1; i < n; i++) // Start from i = 1 so that i != 0
    {
        if (dp[i][(1 << n) - 1] && roads[i][0])
        {
            end_node = i;
            break;
        }
    }

    if (end_node == -1)
        return {-1};

    int node = end_node;
    int mask = (1 << n) - 1;
    while (node != -1)
    {
        path.push_back(node);
        int next = parent[node][mask];
        mask ^= 1 << node;
        node = next;
    }

    reverse(path.begin(), path.end());

    int zero_ind = -1;
    for (int i = 0; i < n; i++)
    {
        if (path[i] == 0)
        {
            zero_ind = i;
            break;
        }
    }
    rotate(path.begin(), path.begin() + zero_ind, path.end());
    path.push_back(0);
    return path;
}

signed main()
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

    vector<int> path = check_cycle(n, roads);
    if (path[0] == -1)
    {
        cout << -1 << endl;
        return 0;
    }

    cout << 1 << endl;
    for (auto i : path)
        cout << i << ' ';
    cout << endl;
}