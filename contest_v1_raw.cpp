//////////////////////////////////////////////////////////////////
// "Code is like humor. When you have to explain it, it’s bad." //
//                        PixlatedBatman                        //
//////////////////////////////////////////////////////////////////
#include <bits/stdc++.h>
#define llt long long int
#define ld long double
#define vllt vector<llt>
#define vpair vector<pair<llt, llt>>
#define vvllt vector<vllt>
#define cinv(v)        \
    for (auto &iz : v) \
    cin >> iz
#define asc(v) v.begin(), v.end()
#define des(v) v.rbegin(), v.rend()
#define vsort(v) sort(asc(v))
#define vrsort(v) sort(des(v))
#define sllt set<llt>
#define stllt stack<llt>
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define L(i, j, k) for (llt i = (j); i < (k); i++)
#define LL(i, v) for (auto i : v)
#define R(i, j, k) for (llt i = (j); i > (k); i--)
#define endl "\n"
#define print(xz) cout << xz << endl
const llt INF = 1e9 + 7;
const llt MOD = 998244353;
#define no cout << "NO" << endl
#define yes cout << "YES" << endl
using namespace std;

llt gcd(llt a, llt b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
llt lcm(llt a, llt b) { return a * b / gcd(a, b); }
llt to_int(char c) { return int(c - '0'); }
char to_char(int i) { return char(i + int('0')); }
vllt to_vector(string s)
{
    vllt v;
    LL(i, s)
    v.pb(to_int(i));
    return v;
}
string to_string(vllt v)
{
    string s = "";
    LL(i, v)
    s += to_char(i);
    return s;
}

bool compare_dist(vllt &x, vllt &y, int i, int j)
{
    float dist1 = pow(x[i] * x[i] + y[i] * y[i], 0.5);
    float dist2 = pow(x[j] * x[j] + y[j] * y[j], 0.5);

    return dist1 < dist2;
}

double euclidean(llt x1, llt y1, llt x2, llt y2)
{
    return hypot(x1 - x2, y1 - y2); // faster than sqrt(a^2 + b^2)
}

void Main()
{
    double n, x1, y1, v1;
    double t1, t2, s;
    cin >> n;
    vector<double> x(n), y(n), v(n);

    L(i, 0, n)
    {
        cin >> x1 >> y1 >> v1;
        x[i] = x1;
        y[i] = y1;
        v[i] = v1;
    }

    cin >> s >> t1 >> t2;

    vector<int> best_tour;
    double best_cost = 1e18;
    int restart_limit = 1;

    double gold_total = 0;
    LL(i, v)
    gold_total += i;

    while (restart_limit--)
    {
        vector<bool> visited(n, false);
        vector<int> tour;
        // int current = rand() % n;

        int best_start = 0;
        double min_start_dist = 1e18;
        for (int i = 0; i < n; i++)
        {
            double d = euclidean(x[i], y[i], 0, 0);
            if (d < min_start_dist)
            {
                min_start_dist = d;
                best_start = i;
            }
        }
        int current = best_start;

        // int current = 0;
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
                        score += 1 / dist;

                    // score += (rand() % 1000) * 1e-6; // noise

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

        // double total_len = 0;
        // for (int i = 0; i + 1 < n; ++i)
        //     total_len += euclidean(x[tour[i]], y[tour[i]], x[tour[i + 1]], y[tour[i + 1]]);
        // // total_len += euclidean(x[tour[n - 1]], y[tour[n - 1]], x[tour[0]], y[tour[0]]);

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
            // current = i;
        }

        // if (total_len < best_cost)
        // {
        //     best_cost = total_len;
        //     best_tour = tour;
        // }

        double score = gold_acc * 200.0 / gold_total;
        if (score < best_cost)
        {
            best_cost = score;
            best_tour = tour;
        }
    }

    cout << best_tour.size() << endl;
    LL(i, best_tour)
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