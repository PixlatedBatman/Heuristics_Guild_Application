//////////////////////////////////////////////////////////////////
// "Code is like humor. When you have to explain it, it’s bad." //
//                        PixlatedBatman                        //
//////////////////////////////////////////////////////////////////
#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
using namespace chrono;

typedef vector<int> vi;

int n;
double s, t1, t2;
vector<double> x, y, v;

// Euclidean distance between two points
double euclidean(int i, int j)
{
    return hypot(x[i] - x[j], y[i] - y[j]);
}

// Evaluate the score of a tour
double evaluate(const vi &tour)
{
    double total_gold = accumulate(v.begin(), v.end(), 0.0);
    double collected_gold = v[tour[0]];
    double time_elapsed = euclidean(tour[0], 0) / s;

    for (int i = 1; i < tour.size(); ++i)
    {
        if (time_elapsed > t2)
            break;
        time_elapsed += euclidean(tour[i - 1], tour[i]) / s;
        if (time_elapsed <= t2)
            collected_gold += v[tour[i]];
    }
    return collected_gold * 200.0 / total_gold;
}

vi generate_random_tour()
{
    vi tour(n);
    iota(tour.begin(), tour.end(), 0);
    shuffle(tour.begin(), tour.end(), rng);
    return tour;
}

// Basic greedy heuristic for seeding
vi greedy_tour()
{
    vector<bool> visited(n, false);
    vi tour;
    int curr = rng() % n;
    tour.push_back(curr);
    visited[curr] = true;
    for (int i = 1; i < n; ++i)
    {
        double best_dist = 1e18;
        int next = -1;
        for (int j = 0; j < n; ++j)
        {
            if (!visited[j])
            {
                double d = euclidean(curr, j);
                if (d < best_dist)
                    best_dist = d, next = j;
            }
        }
        if (next != -1)
        {
            tour.push_back(next);
            visited[next] = true;
            curr = next;
        }
    }
    return tour;
}

// Tournament selection
vi tournament_selection(const vector<pair<double, vi>> &population, int k = 3)
{
    vi best;
    double best_score = -1e18;
    for (int i = 0; i < k; ++i)
    {
        int idx = rng() % population.size();
        if (population[idx].first > best_score)
        {
            best_score = population[idx].first;
            best = population[idx].second;
        }
    }
    return best;
}

// Order crossover
vi crossover(const vi &p1, const vi &p2)
{
    int l = rng() % n, r = rng() % n;
    if (l > r)
        swap(l, r);
    vi child(n, -1);
    set<int> seen;
    for (int i = l; i <= r; ++i)
    {
        child[i] = p1[i];
        seen.insert(p1[i]);
    }
    int ptr = 0;
    for (int i = 0; i < n; ++i)
    {
        if (!seen.count(p2[i]))
        {
            while (child[ptr] != -1)
                ++ptr;
            child[ptr] = p2[i];
        }
    }
    return child;
}

void mutate(vi &tour, double mutation_rate = 0.2)
{
    if ((rng() % 1000) / 1000.0 < mutation_rate)
    {
        int i = rng() % n;
        int j = rng() % n;
        swap(tour[i], tour[j]);
    }
}

void two_opt(vi &tour)
{
    bool improved = true;
    while (improved)
    {
        improved = false;
        for (int i = 1; i < n - 1; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                double before = euclidean(tour[i - 1], tour[i]) + euclidean(tour[j], tour[(j + 1) % n]);
                double after = euclidean(tour[i - 1], tour[j]) + euclidean(tour[i], tour[(j + 1) % n]);
                if (after < before)
                {
                    reverse(tour.begin() + i, tour.begin() + j + 1);
                    improved = true;
                }
            }
        }
    }
}

void Main()
{
    cin >> n;
    x.resize(n);
    y.resize(n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i] >> v[i];
    cin >> s >> t1 >> t2;

    int population_size = 150;
    vector<pair<double, vi>> population;
    double mutation_rate = 0.2;

    for (int i = 0; i < population_size; ++i)
    {
        vi tour = greedy_tour();
        for (int j = 0; j < 3; ++j)
            mutate(tour, 1.0);
        double score = evaluate(tour);
        population.push_back({score, tour});
    }

    auto start_time = high_resolution_clock::now();
    int stagnation = 0;
    double best_score = population[0].first;

    while (duration<double>(high_resolution_clock::now() - start_time).count() < 1.0)
    {
        vector<pair<double, vi>> new_population;
        sort(population.rbegin(), population.rend());
        new_population.push_back(population[0]);

        while (new_population.size() < population_size)
        {
            vi p1 = tournament_selection(population);
            vi p2 = tournament_selection(population);
            vi child = crossover(p1, p2);
            mutate(child, mutation_rate);
            two_opt(child);
            new_population.emplace_back(evaluate(child), child);
        }

        if (abs(new_population[0].first - best_score) < 1e-9)
        {
            stagnation++;
            if (stagnation >= 50)
                mutation_rate = min(1.0, mutation_rate * 1.5);
        }
        else
        {
            stagnation = 0;
            best_score = new_population[0].first;
            mutation_rate = 0.2;
        }

        population = move(new_population);
    }

    auto best = max_element(population.begin(), population.end());
    cout << best->second.size() << '\n';
    for (int i : best->second)
        cout << i << ' ';
    cout << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    Main();
    return 0;
}