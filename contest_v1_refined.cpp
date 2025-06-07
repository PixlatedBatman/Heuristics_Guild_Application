//////////////////////////////////////////////////////////////////
// "Code is like humor. When you have to explain it, it’s bad." //
//                        PixlatedBatman                        //
//////////////////////////////////////////////////////////////////
#include <bits/stdc++.h>
using namespace std;

double euclidean(int x1, int y1, int x2, int y2)
{
    return hypot(x1 - x2, y1 - y2); // faster than sqrt(a^2 + b^2)
}

void Main()
{
    double n, x1, y1, v1;
    double t1, t2, s;
    cin >> n;
    vector<double> x(n), y(n), v(n);

    for (int i = 0; i < n; i++)
    {
        cin >> x1 >> y1 >> v1;
        x[i] = x1;
        y[i] = y1;
        v[i] = v1;
    }
    cin >> s >> t1 >> t2;

    double gold_total = 0;
    for (auto i : v)
        gold_total += i;

    vector<bool> visited(n, false);
    vector<int> tour;

    int best_start = 0;
    double min_start_dist = 1e18;
    for (int i = 0; i < n; i++)
    {
        double d = euclidean(x[i], y[i], 0, 0) / v[i];
        if (d < min_start_dist)
        {
            min_start_dist = d;
            best_start = i;
        }
    }
    int current = best_start;

    visited[current] = true;
    tour.push_back(current);
    double time_elapsed = min_start_dist / s;

    while (tour.size() < n)
    {
        double best_score = -1e18;
        int next = -1;

        for (int i = 0; i < n; ++i)
        {
            if (!visited[i])
            {
                double dist = euclidean(x[current], y[current], x[i], y[i]);
                if (dist == 0)
                    dist = 1e-6;

                double score;
                if (time_elapsed <= t1)
                    score = (double)v[i] / dist;
                else if (time_elapsed <= t2)
                    score = (10.0 / dist + 1.0 * (double)v[i] / dist) / 11;
                else
                    score = 1 / dist;

                if (score > best_score)
                {
                    best_score = score;
                    next = i;
                }
            }
        }

        double dist = euclidean(x[current], y[current], x[next], y[next]);
        time_elapsed += dist / s;

        visited[next] = true;
        tour.push_back(next);
        current = next;
    }

    current = tour[0];
    double gold_acc = v[current];
    time_elapsed = euclidean(x[tour[0]], y[tour[0]], 0, 0) / s;

    for (int i = 1; i < n; i++)
    {
        if (time_elapsed <= t2)
        {
            gold_acc += v[tour[i]];
        }
        else
            break;

        time_elapsed += euclidean(x[tour[i - 1]], y[tour[i - 1]], x[tour[i]], y[tour[i]]) / s;
    }

    double score = gold_acc * 200.0 / gold_total;

    cout << tour.size() << endl;
    for (auto i : tour)
        cout << i << ' ';
    cout << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Main();
    return 0;
}